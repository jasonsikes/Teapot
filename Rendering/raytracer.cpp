#include "raytracer.h"

#include "QtCore/qdebug.h"
#include "QtGui/qguiapplication.h"
#include "Textures/light.h"
#include "Textures/texture.h"
#include "scene.h"
#include "Objects/shape.h"
#include "Textures/shader.h"
#include <QDebug>

// Some support functions
inline QVector3D reflect(const QVector3D& v, const QVector3D& n) {
    return v - 2*QVector3D::dotProduct(v,n)*n;
}

inline QVector3D refract(const QVector3D& normal, const QVector3D& incident,
               float n)
{
    const float cosI = -QVector3D::dotProduct(normal, incident);
    const float sinT2 = n * n * (1.0f - cosI * cosI);
    if(sinT2 > 1.0f) return QVector3D(); // TIR
    const float cosT = sqrtf(1.0 - sinT2);
    return n * incident + (n * cosI - cosT) * normal;
}

// Debug mode is disabled at the start of execution and then enabled when rendering has completed.
// In debugging mode the user can click on a pixel to trigger a raytrace from that pixel
// with some debugging messsages being printed to the console.
bool enableDebug = false;


auto jDebug(int depth)
{
    QString prefix(depth,'>');
    return (qDebug()<<prefix);
}

Raytracer::Raytracer(Scene *aScene)
    : scene(aScene)
{
}

RGBA Raytracer::rgbAtIJ(float i, float j)
{
    Ray r = scene->camera.getRay(i, j, scene->cameraXi1, scene->cameraXi2);
    return traceRay(r, 15);
}

RGBA Raytracer::traceRay(Ray r, int depth, bool rayIsInside)
{
    const float rayOriginationEpsilon = 0.001;
    HitRecord rec;
    float tmax = 100000;
    bool is_a_hit = false;
    QList<Light *>directLights;

    // find the closest object that the ray hits.
    for (auto k : scene->shapes)
        if (k->hit(r, rayOriginationEpsilon, tmax, rec)) {
            tmax = rec.t;
            is_a_hit = true;
        }

    // if no object is hit, return the background color
    if (!is_a_hit)
        return scene->backgroundColor;

    // process the hit object
    rec.hitObject->processHit(r, rec);
    QVector3D normal = rec.normal;
    if (enableDebug) {
        jDebug(depth) << "normal: " << normal;
    }
    QVector3D rDirection = r.direction().normalized();

    // Initialize the local, reflection, and transmission colors.
    RGBA iReflect = {0,0,0,0};
    RGBA iTransmit = {0,0,0,0};
    RGBA iLocal = {0,0,0,1};
    float reflectionProportion = 0;
    float transmissionProportion = 0;

    // If we still haven't reached the maximum depth, we can continue to trace the ray.
    if (depth > 0) {
        float IdotN = QVector3D::dotProduct(rDirection, normal);
        bool rayIsEntering = IdotN < 0;
        if (enableDebug) {
            jDebug(depth) << "rDirection: " << rDirection;
            jDebug(depth) << "normal: " << normal;
            jDebug(depth) << "IdotN: " << IdotN;
            jDebug(depth) << "rayIsEntering: " << rayIsEntering;
        }

        // Reflection and transmission are determined by the brightness of the colors.
        reflectionProportion = rec.hitObject->getReflection()->applyTexture(&rec).value();
        transmissionProportion = rec.hitObject->getTransparency()->applyTexture(&rec).value();

        if (transmissionProportion > 0.01f) {
            int tDepth = depth;
            if ( ! rayIsEntering) --tDepth;

            float n = rec.hitObject->getIndexOfRefraction();
            if ( ! rayIsEntering) {
                n = 1.0f / n;
                normal = -normal;
            }
            QVector3D transmitRayDir = refract(normal, rDirection, 1.0f / n);
            if (transmitRayDir == QVector3D()) {
                // Total internal reflection
                reflectionProportion = 1;
                transmissionProportion = 0;
            } else {
                Ray transmitRay(rec.hit_p, transmitRayDir);
                iTransmit = traceRay(transmitRay, tDepth, rayIsEntering);

                if ( ! rayIsEntering) {
                    // Interior shading is simply passed on through to the caller.
                    return iTransmit;
                }
            }
        }

        --depth;

        if (reflectionProportion > 0.01f) {
            QVector3D reflectRayDir = reflect(rDirection, normal);
            Ray reflectRay(rec.hit_p, reflectRayDir);
            iReflect = traceRay(reflectRay, depth);
        }
    }
    // calculate local illumination
    for (auto k : scene->lights) {
        bool lightIsBlocked = false;
        QVector3D rayTemp = k->location - rec.hit_p;
        Ray lightRay(rec.hit_p, rayTemp.normalized());
        for (auto sk : scene->shapes) {
            if (sk->shadowHit(lightRay, 0.01, rayTemp.length())) {
                lightIsBlocked = true;
                break;
            }
        }
        if ( ! lightIsBlocked) {
            directLights.push_back(k);
        }
    }

    iLocal = rec.hitObject->getTexture()->applyTexture(&rec);
    iLocal = rec.hitObject->getShader()->applyDiffuse(iLocal, rec, rDirection, scene->lights, directLights);

    iLocal = iLocal * (1 - transmissionProportion) + iTransmit * transmissionProportion;
    iLocal = iLocal * (1 - reflectionProportion) + iReflect * reflectionProportion;


    iLocal = rec.hitObject->getShader()->applySpecular(iLocal, rec, rDirection, scene->lights, directLights);

    return iLocal;

}


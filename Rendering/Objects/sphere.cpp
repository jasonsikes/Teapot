#include "sphere.h"
#include "../Core/ray.h"
#include <QMatrix4x4>


Sphere::Sphere(const QVector3D & _center,
               const QVector3D & _orientation,
               float _radius,
               const Texture *_texture,
               const Shader *_shader,
               const Shader *_reflection,
               float _indexOfRefraction,
               const Shader *_transparency)
    : center(_center), orientation(_orientation), radius(_radius), texture(_texture), reflection(_reflection),
    shader(_shader), indexOfRefraction(_indexOfRefraction), transparency(_transparency)
{ }


bool Sphere::hit(const Ray & r, float tmin, float tmax, HitRecord & record) const
{
    QVector3D temp = r.origin() - center;

    float a = QVector3D::dotProduct(r.direction(), r.direction());
    float b = 2*QVector3D::dotProduct(r.direction(), temp);
    float c = QVector3D::dotProduct(temp, temp) - radius * radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        float t = (-b - discriminant) / (2*a);

        if (t < tmin)
            t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax)
            return false;

        record.t = t;
        record.hitObject = this;

        return true;
    }
    return false;
}


void Sphere::processHit(const Ray & r, HitRecord &record) const
{
    record.normal = (r.origin() + record.t * r.direction() - center).normalized();
    record.hit_p = (r.origin() + record.t * r.direction());

    // Rotate the normal by the sphere's orientation
    QQuaternion rotation = QQuaternion::fromDirection(orientation, QVector3D(0, 1, 0));
    QVector3D adjustedNormal = rotation.rotatedVector(record.normal);

    // theta and phi need to be between 0 and 1.
    float theta = acos(adjustedNormal.y()) / M_PI;
    float phi = (atan2(adjustedNormal.z(), adjustedNormal.x()) / (2.0f * M_PI)) + 0.5f;
    record.uv = QVector2D(phi, theta);
}


const Texture * Sphere :: getTexture() const
{
    return texture;
}


const Shader * Sphere :: getShader() const
{
    return shader;
}


const Shader * Sphere :: getReflection() const
{
    return reflection;
}


float Sphere::getIndexOfRefraction() const
{
    return indexOfRefraction;
}


const Shader * Sphere::getTransparency() const
{
    return transparency;
}


bool Sphere::shadowHit(const Ray & r, float tmin, float tmax) const
{
    QVector3D temp = r.origin() - center;

    float a = QVector3D::dotProduct(r.direction(), r.direction());
    float b = 2*QVector3D::dotProduct(r.direction(), temp);
    float c = QVector3D::dotProduct(temp, temp) - radius * radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        float t = (-b - discriminant) / (2*a);

        if (t < tmin)
            t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax)
            return false;

        return true;
    }
    return false;
}

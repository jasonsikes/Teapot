#include "shader.h"
#include "light.h"

PhongShader :: PhongShader(float _shininess)
    :shininess(_shininess)
{ }


RGBA PhongShader :: applyDiffuse(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                                const QList<Light *> &ambientLights, const QList<Light *> &directLights) const
{
    RGBA iLocal(0,0,0,1);

    for (auto k : ambientLights) {
        iLocal += k->ambientColor * sourceColor;
    }

    for (auto k : directLights) {
        QVector3D light = (k->location - rec.hit_p).normalized();
        //QVector3D eye = -_eye.normalized();

        float Kd = fmax(QVector3D::dotProduct(rec.normal,light), 0.0f);

        RGBA diffuse = k->diffuseColor * Kd;
        iLocal += diffuse * sourceColor;
    }
    return iLocal;
}

RGBA PhongShader :: applySpecular(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                                 const QList<Light *> &ambientLights, const QList<Light *> &directLights) const
{
    RGBA iLocal(sourceColor);

    for (auto k : directLights) {
        QVector3D light = (k->location - rec.hit_p).normalized();
        QVector3D eye = -_eye.normalized();
        QVector3D half = (eye + light).normalized();

        float Ks = powf(fmax(QVector3D::dotProduct(half, rec.normal), 0.0f), shininess);

        RGBA specular = (QVector3D::dotProduct(rec.normal, light) >= 0) ? k->specularColor * Ks : RGBA(0,0,0,1);
        iLocal += specular;
    }
    return iLocal;
}


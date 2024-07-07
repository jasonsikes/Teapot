#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Core/rgba.h"
#include "..//Objects/shape.h"
#include <QList>
#include <QVector3D>


class Light;

// The parent class for shaders. Currently, only PhongShader is implemented.
struct Shader
{
    virtual RGBA applyDiffuse(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                             const QList<Light *> &ambientLights, const QList<Light *> &directLights) const = 0;
    virtual RGBA applySpecular(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                              const QList<Light *> &ambientLights, const QList<Light *> &directLights) const = 0;
    virtual ~Shader() {}
};

struct PhongShader : public Shader
{
    PhongShader(float _shininess);
    RGBA applyDiffuse(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                     const QList<Light *> &ambientLights, const QList<Light *> &directLights) const;
    RGBA applySpecular(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                      const QList<Light *> &ambientLights, const QList<Light *> &directLights) const;
    float shininess;
};

#endif // TEXTURE_H

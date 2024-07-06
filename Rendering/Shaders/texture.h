#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Core/rgba.h"
#include "..//Objects/shape.h"
#include <QList>
#include <QVector3D>


class Light;

// The parent class for textures. Currently, only PhongTexture is implemented.
struct Texture
{
    virtual RGBA applyDiffuse(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                             const QList<Light *> &ambientLights, const QList<Light *> &directLights) const = 0;
    virtual RGBA applySpecular(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                              const QList<Light *> &ambientLights, const QList<Light *> &directLights) const = 0;
    virtual ~Texture() {}
};

struct PhongTexture : public Texture
{
    PhongTexture(float _shininess);
    RGBA applyDiffuse(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                     const QList<Light *> &ambientLights, const QList<Light *> &directLights) const;
    RGBA applySpecular(RGBA sourceColor, HitRecord &rec, const QVector3D &_eye,
                      const QList<Light *> &ambientLights, const QList<Light *> &directLights) const;
    float shininess;
};

#endif // TEXTURE_H

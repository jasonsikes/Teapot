#ifndef SHAPE_H
#define SHAPE_H

#include <QVector3D>

class Ray;
class Shader;
class Texture;
class Shape;

/// \brief Store information about a ray intersection with a shape.
/// It includes the time of intersection (t), the normal at the intersection
/// point, the hit point, the UV coordinates, and a pointer to the hit object.
struct HitRecord
{
    float t;
    QVector3D normal;
    QVector3D hit_p;
    QVector2D uv;
    const Shape *hitObject;
};

/// \brief An abstract base class for all shapes in the rendering system.
/// It contains pure virtual functions that must be implemented by any derived
/// class. These functions include hit detection, shadow hit detection,
/// processing hits, and retrieving various properties such as shader, texture,
/// reflection, index of refraction, and transparency.
struct Shape
{
    virtual ~Shape() {}
    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord & record) const = 0;
    virtual bool shadowHit(const Ray & r, float tmin, float tmax) const = 0;
    virtual void processHit(const Ray &r,HitRecord &record) const = 0;
    virtual const Shader * getShader() const = 0;
    virtual const Texture *getTexture() const = 0;
    virtual const Texture * getReflection() const = 0;
    virtual float getIndexOfRefraction() const = 0;

    // TODO: transparency should be the alpha component of getTexture.
    virtual const Texture * getTransparency() const = 0;
};


inline QVector3D lerp(const QVector3D &a, const QVector3D &b, float u)
{
    float t = 1.0f - u;
    return {a.x() * t + b.x() * u,
            a.y() * t + b.y() * u,
            a.z() * t + b.z() * u};

}

#endif // SHAPE_H

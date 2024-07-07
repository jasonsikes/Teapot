#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

// The Sphere class represents a sphere in the scene.
struct Sphere : public Shape
{
    QVector3D center;
    QVector3D orientation;
    float radius;
    const Shader *shader;
    const Texture *texture;
    const Texture *reflection;
    float indexOfRefraction;
    const Texture *transparency;

    Sphere(const QVector3D & _center,
           const QVector3D & _orientation,
           float _radius,
           const Shader *_shader,
           const Texture *_texture,
           const Texture *_reflection,
           float _indexOfRefraction,
           const Texture *_transparency);

    bool hit(const Ray & r, float tmin, float tmax, HitRecord & record) const;
    bool shadowHit(const Ray & r, float tmin, float tmax) const;
    void processHit(const Ray & r, HitRecord &record) const;
    const Shader * getShader() const;
    const Texture * getTexture() const;
    const Texture * getReflection() const;
    float getIndexOfRefraction() const;
    const Texture * getTransparency() const;
};

#endif // SPHERE_H

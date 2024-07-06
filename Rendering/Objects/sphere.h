#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

// The Sphere class represents a sphere in the scene.
struct Sphere : public Shape
{
    QVector3D center;
    QVector3D orientation;
    float radius;
    const Texture *texture;
    const Shader *shader;
    const Shader *reflection;
    float indexOfRefraction;
    const Shader *transparency;

    Sphere(const QVector3D & _center,
           const QVector3D & _orientation,
           float _radius,
           const Texture *_texture,
           const Shader *_shader,
           const Shader *_reflection,
           float _indexOfRefraction,
           const Shader *_transparency);

    bool hit(const Ray & r, float tmin, float tmax, HitRecord & record) const;
    bool shadowHit(const Ray & r, float tmin, float tmax) const;
    void processHit(const Ray & r, HitRecord &record) const;
    const Texture * getTexture() const;
    const Shader * getShader() const;
    const Shader * getReflection() const;
    float getIndexOfRefraction() const;
    const Shader * getTransparency() const;
};

#endif // SPHERE_H

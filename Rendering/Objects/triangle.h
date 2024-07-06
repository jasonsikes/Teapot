#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

// The Triangle class represents a triangle in the scene.
struct Triangle : public Shape
{

    QVector3D p0, p1, p2;
    QVector2D t0, t1, t2;
    QVector3D n0, n1, n2;
    float indexOfRefraction;
    const Shader *transparency;

    const Texture *texture;
    const Shader *shader;
    const Shader *reflection;

    Triangle(const QVector3D & _p0,
             const QVector3D & _p1,
             const QVector3D & _p2,
             const QVector2D & _t0,
             const QVector2D & _t1,
             const QVector2D & _t2,
             const QVector3D & _n0,
             const QVector3D & _n1,
             const QVector3D & _n2,
             const Texture *_texture,
             const Shader *_shader,
             const Shader *_reflection,
             float _indexOfRefraction,
             const Shader *_transparency);

    // Calculate the normal via cross-product
    Triangle(const QVector3D & _p0,
             const QVector3D & _p1,
             const QVector3D & _p2,
             const QVector2D & _t0,
             const QVector2D & _t1,
             const QVector2D & _t2,
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

#endif // TRIANGLE_H

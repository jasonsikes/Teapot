#ifndef PLANE_H
#define PLANE_H

#include "shape.h"

// The Plane class represents an infinite plane in the scene.
struct Plane : public Shape
{
    QVector3D normal;
    QVector3D point;
    QVector3D vVec;
    QVector3D uVec;
    QVector2D vecLength;
    QVector3D uNorm;
    QVector3D vNorm;
    const Shader *shader;
    const Texture *texture;
    const Texture *reflection;
    float indexOfRefraction;
    const Texture *transparency;

    Plane(const QVector3D & _vVec,
          const QVector3D & _uVec,
          const QVector3D & _point,
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
    const Texture *getTransparency() const;
};


struct Water : public Plane
{
    Water(const QVector3D & _vVec,
          const QVector3D & _uVec,
          const QVector3D & _point,
          const Shader *_shader,
          const Texture *_texture,
          const Texture *_reflection,
          float _indexOfRefraction,
          const Texture *_transparency)
        : Plane(_vVec, _uVec, _point, _shader, _texture, _reflection, _indexOfRefraction, _transparency)
    {}

    void processHit(const Ray & r, HitRecord &record) const;

};

#endif // PLANE_H

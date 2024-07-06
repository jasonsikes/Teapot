#ifndef TRIANGLEGROUP_H
#define TRIANGLEGROUP_H

#include "triangle.h"
#include "bbox.h"
#include <QList>

// The TriangleGroup class represents a group of triangles in the scene.
// A group of triangles share a bounding box.
struct TriangleGroup : public Shape
{
    float indexOfRefraction;
    const Shader *transparency;

    const Texture *texture;
    const Shader *shader;
    const Shader *reflection;

    QList<Triangle> triangles;
    BBox box;

    TriangleGroup(QList<Triangle>_triangles);

    bool hit(const Ray & r, float tmin, float tmax, HitRecord & record) const;
    bool shadowHit(const Ray & r, float tmin, float tmax) const;
    void processHit(const Ray & r, HitRecord &record) const;
    const Texture * getTexture() const;
    const Shader * getShader() const;
    const Shader * getReflection() const;
    float getIndexOfRefraction() const;
    const Shader * getTransparency() const;



};

#endif // TRIANGLEGROUP_H

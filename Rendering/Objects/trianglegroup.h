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
    const Texture *transparency;

    const Shader *shader;
    const Texture *texture;
    const Texture *reflection;

    QList<Triangle> triangles;
    BBox box;

    TriangleGroup(QList<Triangle>_triangles);

    bool hit(const Ray & r, float tmin, float tmax, HitRecord & record) const;
    bool shadowHit(const Ray & r, float tmin, float tmax) const;
    void processHit(const Ray & r, HitRecord &record) const;
    const Shader * getShader() const;
    const Texture * getTexture() const;
    const Texture * getReflection() const;
    float getIndexOfRefraction() const;
    const Texture * getTransparency() const;



};

#endif // TRIANGLEGROUP_H

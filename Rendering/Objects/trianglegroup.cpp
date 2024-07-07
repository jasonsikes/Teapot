#include "trianglegroup.h"

TriangleGroup :: TriangleGroup(QList<Triangle>_triangles)
    : triangles(_triangles)
{
    box = BBox(triangles);
}

bool TriangleGroup :: hit(const Ray & r, float tmin, float tmax, HitRecord & record) const
{
    if (!box.rayIntersect(r, tmin, tmax))
        return false;
    // The ray is somewhere in the box.
    // search each triangle for a hit
    bool hasHit = false;
    for (auto &t : triangles) {
        if (t.hit(r,tmin,tmax, record)) {
            hasHit = true;
            tmax = record.t;
        }
    }
    return hasHit;
}

void TriangleGroup :: processHit(const Ray & r, HitRecord &record) const
{
    // processHit should be handled by the underlying triangles.
    assert(false);
}

const Shader * TriangleGroup :: getShader() const
{
    return shader;
}

const Texture * TriangleGroup :: getTexture() const
{
    return texture;
}

const Texture * TriangleGroup :: getReflection() const
{
    return reflection;
}

const Texture * TriangleGroup :: getTransparency() const
{
    return transparency;
}

float TriangleGroup :: getIndexOfRefraction() const
{
    return indexOfRefraction;
}


bool TriangleGroup::shadowHit(const Ray & r, float tmin, float tmax) const
{
    if (!box.rayIntersect(r, tmin, tmax))
        return false;
    // The ray is somewhere in the box.
    // search each triangle for a hit
    for (auto &t : triangles) {
        if (t.shadowHit(r,tmin,tmax))
            return true;
    }
    return false;
}

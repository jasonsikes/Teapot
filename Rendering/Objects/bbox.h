#ifndef BBOX_H
#define BBOX_H

#include <QList>
#include "../Core/ray.h"

class Triangle;

// The BBox class represents a bounding box.
// Other, more complex, objects may use this class to quickly rule out whether a ray
// intersects the object.
class BBox {
    QVector3D pp[2];
public:
    BBox(const QVector3D& a, const QVector3D& b) { pp[0] = a; pp[1] = b; }
    BBox(const QVector3D& a) { pp[0] = pp[1] = a; }
    BBox() {}
    BBox(QList<Triangle> triangles);
    QVector3D min() const { return pp[0]; }
    QVector3D max() const { return pp[1]; }
    bool rayIntersect(const Ray& r, float tmin, float tmax) const;
    void include(const QVector3D& a);
};

inline void BBox::include(const QVector3D& a)
{
    if (a.x() < pp[0].x()) pp[0].setX(a.x());
    if (a.y() < pp[0].y()) pp[0].setY(a.y());
    if (a.z() < pp[0].z()) pp[0].setZ(a.z());
    if (a.x() > pp[1].x()) pp[1].setX(a.x());
    if (a.y() > pp[1].y()) pp[1].setY(a.y());
    if (a.z() > pp[1].z()) pp[1].setZ(a.z());
}


inline bool BBox::rayIntersect(const Ray& r, float tmin, float tmax) const {

    float interval_min = tmin;
    float interval_max = tmax;

    float t0 = (pp[r.posneg[0]].x() - r.data[0].x()) * r.data[2].x();
    float t1 = (pp[r.posneg[1]].x() - r.data[0].x()) * r.data[2].x();
    if (t0 > interval_min) interval_min = t0;
    if (t1 < interval_max) interval_max = t1;
    if (interval_min > interval_max) return false;

    t0 = (pp[r.posneg[2]].y() - r.data[0].y()) * r.data[2].y();
    t1 = (pp[r.posneg[3]].y() - r.data[0].y()) * r.data[2].y();
    if (t0 > interval_min) interval_min = t0;
    if (t1 < interval_max) interval_max = t1;
    if (interval_min > interval_max) return false;

    t0 = (pp[r.posneg[4]].z() - r.data[0].z()) * r.data[2].z();
    t1 = (pp[r.posneg[5]].z() - r.data[0].z()) * r.data[2].z();
    if (t0 > interval_min) interval_min = t0;
    if (t1 < interval_max) interval_max = t1;
    return (interval_min <= interval_max);
}


inline BBox surround(const BBox& b1, const BBox& b2) {
    return BBox(
        QVector3D(std::min(b1.min().x(), b2.min().x()),
                  std::min(b1.min().y(), b2.min().y()),
                  std::min(b1.min().z(), b2.min().z())),
        QVector3D(std::max(b1.max().x(), b2.max().x()),
                  std::max(b1.max().y(), b2.max().y()),
                  std::max(b1.max().z(), b2.max().z())));
}

#endif // BBOX_H

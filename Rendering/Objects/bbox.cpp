#include "bbox.h"
#include "triangle.h"

BBox :: BBox(QList<Triangle> triangles)
{
    pp[0] = pp[1] = triangles.first().p0;
    for (auto &t : triangles) {
        include(t.p0);
        include(t.p1);
        include(t.p2);
    }
}



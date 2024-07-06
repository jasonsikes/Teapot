#ifndef RAY_H
#define RAY_H

#include <QVector3D>

// The Ray class represents a ray in the scene.
// It is used to trace the rays from the source (such as a camera,
// light source, or a reflection) to the scene.
struct Ray {
    QVector3D data[3];
    int posneg[6];

    Ray() {}
    Ray(const QVector3D & a, const QVector3D & b)
    {
        data[0] = a;
        data[1] = b;
        data[2] = QVector3D(1.0f / b.x(), 1.0f / b.y(), 1.0f / b.z());

        posneg[0] =  (data[1].x() > 0 ? 0 : 1);
        posneg[1] = posneg[0] ^ 1;

        posneg[2] =  (data[1].y() > 0 ? 0 : 1);
        posneg[3] = posneg[2] ^ 1;

        posneg[4] =  (data[1].z() > 0 ? 0 : 1);
        posneg[5] = posneg[4] ^ 1;
    }

    QVector3D origin() const { return data[0]; }
    QVector3D direction() const { return data[1]; }
    QVector3D pointAtParameter(float t) const
    { return data[0] + t * data[1]; }

};


#endif // RAY_H

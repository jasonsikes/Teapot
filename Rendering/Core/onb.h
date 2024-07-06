#ifndef ONB_H
#define ONB_H

#include <QVector3D>

// The ONB class represents an orthonormal basis.
// It is used to transform the rays from the camera to the scene.
struct ONB
{
    QVector3D U,V,W;

    ONB() {}
    ONB(const QVector3D & a, const QVector3D & b, const QVector3D & c)
    { U = a; V = b; W = c; }

    void initFromU(const QVector3D& u);
    void initFromV(const QVector3D& v);
    void initFromW(const QVector3D& w);

    void set(const QVector3D & a, const QVector3D & b, const QVector3D & c)
    { U = a; V = b; W = c; }

    void initFromUV(const QVector3D & u, const QVector3D & v);
    void initFromVU(const QVector3D & v, const QVector3D & u);
    void initFromUW(const QVector3D & u, const QVector3D & w);
    void initFromWU(const QVector3D & w, const QVector3D & u);
    void initFromVW(const QVector3D & v, const QVector3D & w);
    void initFromWV(const QVector3D & w, const QVector3D & v);

    friend bool operator==(const ONB& o1, const ONB & o2);

    QVector3D u() const { return U; }
    QVector3D v() const { return V; }
    QVector3D w() const { return W; }

};

#endif // ONB_H

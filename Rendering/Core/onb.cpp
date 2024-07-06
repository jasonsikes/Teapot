#include "onb.h"

#define ONB_EPSILON 0.01f

void ONB::initFromU(const QVector3D & u)
{
    QVector3D n(1,0,0);

    QVector3D m(0,1,0);
    U = u.normalized();
    V = QVector3D::crossProduct(U, n);
    if (V.lengthSquared() < ONB_EPSILON)
        V = QVector3D::crossProduct(U, m);
    W = QVector3D::crossProduct(U, V);
}

void ONB::initFromV(const QVector3D & v)
{
    QVector3D n(1,0,0);
    QVector3D m(0,1,0);
    V = v.normalized();
    U = QVector3D::crossProduct(V, n);
    if (U.lengthSquared() < ONB_EPSILON)
        U = QVector3D::crossProduct(V, m);
    W = QVector3D::crossProduct(U, V);
}

void ONB::initFromW(const QVector3D & w)
{
    QVector3D n(1,0,0);
    QVector3D m(0,1,0);
    W = w.normalized();
    U = QVector3D::crossProduct(W, n);
    if (U.length() < ONB_EPSILON)
        U = QVector3D::crossProduct(W, m);
    V = QVector3D::crossProduct(W, U);
}

void ONB::initFromUV(const QVector3D & u, const QVector3D & v)
{
    U = u.normalized();
    W = QVector3D::crossProduct(u,v).normalized();
    V = QVector3D::crossProduct(W,U);
}

void ONB::initFromVU(const QVector3D & v, const QVector3D & u)
{
    V = v.normalized();
    W = QVector3D::crossProduct(u,v).normalized();
    U = QVector3D::crossProduct(V, W);
}

void ONB::initFromUW(const QVector3D & u, const QVector3D & w)
{
    U = u.normalized();
    V = QVector3D::crossProduct(w,u).normalized();
    W = QVector3D::crossProduct(U,V);
}

void ONB::initFromWU(const QVector3D & w, const QVector3D & u)
{
    W = u.normalized();
    V = QVector3D::crossProduct(w,u).normalized();
    U = QVector3D::crossProduct(V,W);
}

void ONB::initFromVW(const QVector3D & v, const QVector3D & w)
{
    V = v.normalized();
    U = QVector3D::crossProduct(v,w).normalized();
    W = QVector3D::crossProduct(U,V);
}

void ONB::initFromWV(const QVector3D & w, const QVector3D & v)
{
    W = w.normalized();
    U = QVector3D::crossProduct(v,w).normalized();
    V = QVector3D::crossProduct(W,U);
}

bool operator==(const ONB & o1, const ONB & o2)
{ return (o1.u() == o2.u()) && (o1.v() == o2.v()) && (o1.w() == o2.w()); }

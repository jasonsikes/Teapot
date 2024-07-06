#ifndef SOLIDNOISE_H
#define SOLIDNOISE_H

#include <QVector3D>

// A solid noise class that generates Perlin noise.
class SolidNoise {
public:
    SolidNoise();
    SolidNoise(int seed);
    float noise(const QVector3D&) const;
    QVector3D vectorNoise(const QVector3D&) const;
    QVector3D vectorTurbulence( const QVector3D&, int) const ;
    float turbulence(const QVector3D&, int) const;
    float dturbulence(const QVector3D&, int, float) const;
    float omega(float) const;
    QVector3D gamma(int, int, int) const;
    int intGamma(int, int) const;
    float knot(int, int, int, QVector3D&) const;
    QVector3D vectorKnot(int, int, int, QVector3D&) const;

    QVector3D grad[16];
    int phi[16];
};


inline float SolidNoise::omega(float t) const {
    t = (t > 0.0)? t : -t;
    return (t < 1.0)?  (-6*t*t*t*t*t + 15*t*t*t*t -10*t*t*t + 1) : 0.0;
}

inline QVector3D SolidNoise::gamma(int i, int j, int k) const
{
    int idx;
    idx = phi[abs(k)%16];
    idx = phi[abs(j + idx) % 16];
    idx = phi[abs(i + idx) % 16];
    return grad[idx];
}

inline float SolidNoise::knot(int i, int j, int k, QVector3D& v) const {
    return ( omega(v.x()) * omega(v.y()) * omega(v.z()) * (QVector3D::dotProduct(gamma(i,j,k),v)) );
}

inline QVector3D SolidNoise::vectorKnot( int i, int j, int k, QVector3D& v)
    const {
    return ( omega(v.x()) * omega(v.y()) * omega(v.z()) * gamma(i,j,k) );
}

inline int SolidNoise::intGamma(int i, int j) const {
    int idx;
    idx = phi[abs(j)%16];
    idx = phi[abs(i + idx) % 16];
    return idx;
}

#endif // SOLIDNOISE_H

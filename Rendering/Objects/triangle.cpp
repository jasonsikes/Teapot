#include "triangle.h"
#include "../Core/ray.h"

Triangle::Triangle(const QVector3D & _p0,
                   const QVector3D & _p1,
                   const QVector3D & _p2,
                   const QVector2D & _t0,
                   const QVector2D & _t1,
                   const QVector2D & _t2,
                   const QVector3D & _n0,
                   const QVector3D & _n1,
                   const QVector3D & _n2,
                   const Texture *_texture,
                   const Shader *_shader,
                   const Shader *_reflection,
                   float _indexOfRefraction,
                   const Shader * _transparency)
    : p0(_p0), p1(_p1), p2(_p2), t0(_t0), t1(_t1), t2(_t2)
    , n0(_n0.normalized()), n1(_n1.normalized()), n2(_n2.normalized())
    , texture(_texture), reflection(_reflection), shader(_shader),
    indexOfRefraction(_indexOfRefraction), transparency(_transparency)
{}

Triangle::Triangle(const QVector3D & _p0,
                   const QVector3D & _p1,
                   const QVector3D & _p2,
                   const QVector2D & _t0,
                   const QVector2D & _t1,
                   const QVector2D & _t2,
                   const Texture *_texture,
                   const Shader *_shader,
                   const Shader *_reflection,
                   float _indexOfRefraction,
                   const Shader *_transparency)
    : p0(_p0), p1(_p1), p2(_p2), t0(_t0), t1(_t1), t2(_t2)
    , texture(_texture), reflection(_reflection), shader(_shader),
    indexOfRefraction(_indexOfRefraction), transparency(_transparency)
{
    n0 = n1 = n2 = QVector3D::normal(p0,p1,p2);
}



bool Triangle::hit(const Ray & r, float tmin, float tmax, HitRecord & record) const
{
    float tval;
    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();

    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();

    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();

    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();

    float EIHF = E*I-H*F;
    float GFDI = G*F-D*I;
    float DHEG = D*H-E*G;

    float denom = A*EIHF + B*GFDI + C*DHEG;
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

    if (beta < 0 || beta >= 1) return false;

    float AKJB = A*K-J*B;
    float JCAL = J*C-A*L;
    float BLKC = B*L-K*C;

    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma < 0 || beta + gamma >= 1) return false;

    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    if (tval >= tmin && tval <= tmax) {
        record.t = tval;
        record.hitObject = this;
            // record.uv is a placeholder for the beta and gamma values.
        // They are not actual uv coordinates (that will happen later)
        record.uv = QVector2D(beta, gamma);
        return true;
    }
    return false;
}

void Triangle::processHit(const Ray & r, HitRecord &record) const
{
    record.hit_p = r.pointAtParameter(record.t);
    float alpha = 1 - record.uv.x() - record.uv.y();
    record.normal = QVector3D(alpha * n0.x() + record.uv.x() * n1.x() + record.uv.y() * n2.x(),
                            alpha * n0.y() + record.uv.x() * n1.y() + record.uv.y() * n2.y(),
                            alpha * n0.z() + record.uv.x() * n1.z() + record.uv.y() * n2.z());
    record.normal.normalize();
    // It's later.
    // Use the UV of the vertices and (beta,gamma) to interpolate UV
    record.uv = QVector2D(alpha * t0.x() + record.uv.x() * t1.x() + record.uv.y() * t2.x(),
                        alpha * t0.y() + record.uv.x() * t1.y() + record.uv.y() * t2.y());
}


const Texture * Triangle :: getTexture() const
{
    return texture;
}

const Shader * Triangle :: getShader() const
{
    return shader;
}

const Shader * Triangle :: getReflection() const
{
    return reflection;
}

const Shader * Triangle :: getTransparency() const
{
    return transparency;
}

float Triangle :: getIndexOfRefraction() const
{
    return indexOfRefraction;
}


bool Triangle::shadowHit(const Ray & r, float tmin, float tmax) const
{
    float tval;
    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();

    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();

    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();

    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();

    float EIHF = E*I-H*F;
    float GFDI = G*F-D*I;
    float DHEG = D*H-E*G;

    float denom = A*EIHF + B*GFDI + C*DHEG;
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

    if (beta < 0 || beta >= 1) return false;

    float AKJB = A*K-J*B;
    float JCAL = J*C-A*L;
    float BLKC = B*L-K*C;

    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma <= 0 || beta + gamma >= 1) return false;

    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    return tval >= tmin && tval <= tmax;
}

#include "plane.h"
#include "../Core/ray.h"

Plane::Plane(const QVector3D & _vVec,
             const QVector3D & _uVec,
             const QVector3D & _point,
             const Shader *_shader,
             const Texture *_texture,
             const Texture *_reflection,
             float _indexOfRefraction,
             const Texture * _transparency)
    : vVec(_vVec), uVec(_uVec), point(_point), shader(_shader), reflection(_reflection), texture(_texture),
    uNorm(_uVec.normalized()), vNorm(_vVec.normalized()), indexOfRefraction(_indexOfRefraction), transparency(_transparency)
{
    normal = QVector3D::crossProduct(uNorm, vNorm);
    vecLength = QVector2D(uVec.length(), vVec.length());
}


bool Plane::hit(const Ray & r, float tmin, float tmax, HitRecord & record) const
{
    float denom = QVector3D::dotProduct(r.direction(), normal);
    if (denom == 0) {
        return false;
    }
    float tval = QVector3D::dotProduct((point - r.origin()), normal) / denom;
    if (tval >= tmin && tval <= tmax) {
        record.t = tval;
        record.hitObject = this;
        return true;
    }
    return false;
}


void Plane::processHit(const Ray & r, HitRecord &record) const
{
    record.normal = normal;
    record.hit_p = (r.origin() + record.t * r.direction());
    QVector3D offset(record.hit_p - point);
    float u1 = QVector3D::dotProduct(uNorm, offset) / vecLength.x();
    float v1 = QVector3D::dotProduct(vNorm, offset) / vecLength.y();
    record.uv = QVector2D(u1, v1);
}


const Shader * Plane :: getShader() const
{
    return shader;
}


const Texture * Plane :: getReflection() const
{
    return reflection;
}


const Texture * Plane :: getTexture() const
{
    return texture;
}


float Plane::getIndexOfRefraction() const
{
    return indexOfRefraction;
}


const Texture * Plane::getTransparency() const
{
    return transparency;
}


bool Plane::shadowHit(const Ray & r, float tmin, float tmax) const
{
    float denom = QVector3D::dotProduct(r.direction(),normal);
    if (denom == 0) return false;
    float tval = QVector3D::dotProduct((point - r.origin()), normal) / denom;
    if (tval >= tmin && tval <= tmax) {
        return true;
    }
    return false;
}



void Water::processHit(const Ray & r, HitRecord &record) const
{
    Plane::processHit(r, record);

    // Apply perturbation to the normal to simulate a wavy surface with more organic variance
    float waveFactor1 = 0.013f; // Adjust this factor to control the wave intensity
    float waveFrequency1 = 4.7f; // Adjust this factor to control the wave frequency

    float waveFactor2 = 0.027f; // Additional wave factor for more variance
    float waveFrequency2 = 2.2f; // Additional wave frequency for more variance

    float waveFactor3 = 0.0015f; // Another wave factor for even more variance
    float waveFrequency3 = 3.7f; // Another wave frequency for even more variance

    // Introduce variance using a combination of sine and cosine functions with different phases
    float waveX = sin(waveFrequency1 * record.hit_p.x() + waveFrequency2 * record.hit_p.y()) * waveFactor1 + 
                  cos(waveFrequency2 * record.hit_p.y() + waveFrequency3 * record.hit_p.z()) * waveFactor2 +
                  sin(waveFrequency3 * record.hit_p.z() + waveFrequency1 * record.hit_p.x()) * waveFactor3;
    float waveY = sin(waveFrequency1 * record.hit_p.y() + waveFrequency2 * record.hit_p.z()) * waveFactor1 + 
                  cos(waveFrequency2 * record.hit_p.z() + waveFrequency3 * record.hit_p.x()) * waveFactor2 +
                  sin(waveFrequency3 * record.hit_p.x() + waveFrequency1 * record.hit_p.y()) * waveFactor3;
    float waveZ = sin(waveFrequency1 * record.hit_p.z() + waveFrequency2 * record.hit_p.x()) * waveFactor1 + 
                  cos(waveFrequency2 * record.hit_p.x() + waveFrequency3 * record.hit_p.y()) * waveFactor2 +
                  sin(waveFrequency3 * record.hit_p.y() + waveFrequency1 * record.hit_p.z()) * waveFactor3;

    QVector3D waveNormal = record.normal + QVector3D(waveX, waveY, waveZ);
    record.normal = waveNormal.normalized();
}

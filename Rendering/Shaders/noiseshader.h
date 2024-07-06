#ifndef NOISESHADER_H
#define NOISESHADER_H

#include "shader.h"
#include "solidnoise.h"

struct NoiseShader : public Shader
{
    float scale;
    const Shader * c0, * c1;
    SolidNoise solidNoise;

    NoiseShader()
    {
    }

    NoiseShader(const Shader * _c0, const Shader * _c1, float _scale = 1)
        : c0(_c0), c1(_c1), scale(_scale)
    { }

    RGBA applyShader(HitRecord *rec) const;
};

#endif // NOISESHADER_H

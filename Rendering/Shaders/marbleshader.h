#ifndef MARBLESHADER_H
#define MARBLESHADER_H

#include "shader.h"
#include "solidnoise.h"

struct MarbleShader : public Shader
{

    float freq, scale;
    int octaves;
    const Shader *  c0, * c1, * c2;
    SolidNoise noise;

    MarbleShader()
    {}

    MarbleShader(const Shader * _c0, const Shader * _c1, const Shader * _c2,
                 float stripesPerUnit, float _scale = 3, int _octaves = 8)
        : c0(_c0), c1(_c1), c2(_c2)
    {
        freq = M_PI * stripesPerUnit;
        scale = _scale;
        octaves = _octaves;
    }

    RGBA applyShader(HitRecord *rec) const;
};

#endif // MARBLESHADER_H

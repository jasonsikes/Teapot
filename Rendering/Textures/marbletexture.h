#ifndef MARBLESHADER_H
#define MARBLESHADER_H

#include "texture.h"
#include "solidnoise.h"

struct MarbleTexture : public Texture
{

    float freq, scale;
    int octaves;
    const Texture *  c0, * c1, * c2;
    SolidNoise noise;

    MarbleTexture()
    {}

    MarbleTexture(const Texture * _c0, const Texture * _c1, const Texture * _c2,
                 float stripesPerUnit, float _scale = 3, int _octaves = 8)
        : c0(_c0), c1(_c1), c2(_c2)
    {
        freq = M_PI * stripesPerUnit;
        scale = _scale;
        octaves = _octaves;
    }

    RGBA applyTexture(HitRecord *rec) const;
};

#endif // MARBLESHADER_H

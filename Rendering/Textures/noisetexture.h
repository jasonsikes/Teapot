#ifndef NOISESHADER_H
#define NOISESHADER_H

#include "texture.h"
#include "solidnoise.h"

struct NoiseTexture : public Texture
{
    float scale;
    const Texture * c0, * c1;
    SolidNoise solidNoise;

    NoiseTexture()
    {
    }

    NoiseTexture(const Texture * _c0, const Texture * _c1, float _scale = 1)
        : c0(_c0), c1(_c1), scale(_scale)
    { }

    RGBA applyTexture(HitRecord *rec) const;
};

#endif // NOISESHADER_H

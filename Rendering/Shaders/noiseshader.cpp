#include "noiseshader.h"
#include "../Objects/shape.h"

RGBA NoiseShader::applyShader(HitRecord *rec) const
{
    float t = (1 + solidNoise.noise(rec->hit_p * scale)) / 2;
    return t * c0->applyShader(rec) + (1 - t) * c1->applyShader(rec);
}

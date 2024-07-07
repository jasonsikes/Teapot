#include "noisetexture.h"
#include "../Objects/shape.h"

RGBA NoiseTexture::applyTexture(HitRecord *rec) const
{
    float t = (1 + solidNoise.noise(rec->hit_p * scale)) / 2;
    return t * c0->applyTexture(rec) + (1 - t) * c1->applyTexture(rec);
}

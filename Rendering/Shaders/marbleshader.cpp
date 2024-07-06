#include "marbleshader.h"
#include "../Objects/shape.h"

RGBA MarbleShader::applyShader(HitRecord *rec) const
{
    float temp = scale * noise.turbulence(freq * rec->hit_p, octaves);
    float t = 2 * fabsf(sinf(freq * rec->hit_p.x() + temp));

    if (t < 1)
        return c1->applyShader(rec) * t + (1 - t) * c2->applyShader(rec);
    else {
        t -= 1;
        return c0->applyShader(rec) * t + (1 - t) * c1->applyShader(rec);
    }
}

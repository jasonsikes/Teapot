#ifndef SHADER_H
#define SHADER_H

#include "../Core/rgba.h"
#include <QImage>

class HitRecord;

// A Shader is the superclass for all shaders.
struct Shader
{
    virtual RGBA applyShader(HitRecord *rec) const = 0;
};


// The simplest shader: uniform color.
struct RgbShader : public Shader
{
    RGBA color;

    RgbShader(const RGBA aColor) : color(aColor) {}

    RGBA applyShader(HitRecord *rec) const
    {
        return color;
    }
};

// A shader that applies a checkerboard pattern to the object.
struct CheckerboardShader : public Shader {
    const Shader* color1;
    const Shader* color2;
    float vMult, uMult;

    CheckerboardShader(const Shader* c1, const Shader* c2,
                       float aVmult = 1, float aUmult = 1)
        : color1(c1), color2(c2), vMult(aVmult), uMult(aUmult) {}

    RGBA applyShader(HitRecord *rec) const override;
};

// A shader that applies a swirl pattern to the object.
struct SwirlShader : public Shader {
    const Shader* color1;
    const Shader* color2;
    float vMult, uMult;

    SwirlShader(const Shader* c1, const Shader* c2,
                float aVmult = 1, float aUmult = 1)
        : color1(c1), color2(c2), vMult(aVmult), uMult(aUmult) {}

    RGBA applyShader(HitRecord *rec) const override;
};

// A shader that applies a repeating gradient to the object.
struct GradientShader : public Shader {
    const Shader* color1;
    const Shader* color2;
    float vMult;

    GradientShader(const Shader* c1, const Shader* c2,
                   float aVmult = 1)
        : color1(c1), color2(c2), vMult(aVmult) {}

    RGBA applyShader(HitRecord *rec) const override;
};

// A shader that applies an image to the object.
struct ImageShader : public Shader {
    QImage image;

    // Loads the image from the given path. The image is expected to be in the
    // same directory as the build folder.
    ImageShader(QString filename);

    RGBA applyShader(HitRecord *rec) const override;
};


#endif // SHADER_H

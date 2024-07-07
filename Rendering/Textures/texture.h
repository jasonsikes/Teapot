#ifndef SHADER_H
#define SHADER_H

#include "../Core/rgba.h"
#include <QImage>

class HitRecord;

// A Texture is the superclass for all textures.
struct Texture
{
    virtual RGBA applyTexture(HitRecord *rec) const = 0;
};


// The simplest texture: uniform color.
struct RgbTexture : public Texture
{
    RGBA color;

    RgbTexture(const RGBA aColor) : color(aColor) {}

    RGBA applyTexture(HitRecord *rec) const
    {
        return color;
    }
};

// A texture that applies a checkerboard pattern to the object.
struct CheckerboardTexture : public Texture {
    const Texture* color1;
    const Texture* color2;
    float vMult, uMult;

    CheckerboardTexture(const Texture* c1, const Texture* c2,
                       float aVmult = 1, float aUmult = 1)
        : color1(c1), color2(c2), vMult(aVmult), uMult(aUmult) {}

    RGBA applyTexture(HitRecord *rec) const override;
};

// A texture that applies a swirl pattern to the object.
struct SwirlTexture : public Texture {
    const Texture* color1;
    const Texture* color2;
    float vMult, uMult;

    SwirlTexture(const Texture* c1, const Texture* c2,
                float aVmult = 1, float aUmult = 1)
        : color1(c1), color2(c2), vMult(aVmult), uMult(aUmult) {}

    RGBA applyTexture(HitRecord *rec) const override;
};

// A texture that applies a repeating gradient to the object.
struct GradientTexture : public Texture {
    const Texture* color1;
    const Texture* color2;
    float vMult;

    GradientTexture(const Texture* c1, const Texture* c2,
                   float aVmult = 1)
        : color1(c1), color2(c2), vMult(aVmult) {}

    RGBA applyTexture(HitRecord *rec) const override;
};

// A texture that applies an image to the object.
struct ImageTexture : public Texture {
    QImage image;

    // Loads the image from the given path. The image is expected to be in the
    // same directory as the build folder.
    ImageTexture(QString filename);

    RGBA applyTexture(HitRecord *rec) const override;
};


#endif // SHADER_H

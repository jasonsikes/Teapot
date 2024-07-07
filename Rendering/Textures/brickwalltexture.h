#ifndef BRICKWALLSHADER_H
#define BRICKWALLSHADER_H

#include "texture.h"
#include <QVector2D>

struct BrickWallTexture : public Texture
{
    const Texture *brickTexture;
    const Texture *mortarTexture;
    QVector2D brickSize;
    QVector2D brickPct;

    BrickWallTexture(const Texture *_brickTexture, const Texture *_mortarTexture, QVector2D _brickSize, QVector2D _brickPct);
    RGBA applyTexture(HitRecord *rec) const;

};

#endif // BRICKWALLSHADER_H

#include "brickwalltexture.h"
#include "../Objects/shape.h"

BrickWallTexture :: BrickWallTexture(const Texture *_brickTexture, const Texture *_mortarTexture, QVector2D _brickSize, QVector2D _brickPct)
    :brickTexture(_brickTexture), mortarTexture(_mortarTexture), brickSize(_brickSize), brickPct(_brickPct)
{ }

RGBA BrickWallTexture :: applyTexture(HitRecord *rec) const
{
    QVector2D position(rec->uv.x() / brickSize.x(), rec->uv.y() / brickSize.y());
    if ((position.x() / 2 - floorf(position.x() / 2)) > 0.5)
        position.setY(position.y() + 0.5);

    position.setX(position.x() - floor(position.x()));
    position.setY(position.y() - floor(position.y()));

    bool useBrick = (position.x() < brickPct.x()) && (position.y() < brickPct.y());
    if (useBrick)
        return brickTexture->applyTexture(rec);
    return mortarTexture->applyTexture(rec);
}

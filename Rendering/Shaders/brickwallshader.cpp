#include "brickwallshader.h"
#include "../Objects/shape.h"

BrickWallShader :: BrickWallShader(const Shader *_brickShader, const Shader *_mortarShader, QVector2D _brickSize, QVector2D _brickPct)
    :brickShader(_brickShader), mortarShader(_mortarShader), brickSize(_brickSize), brickPct(_brickPct)
{ }

RGBA BrickWallShader :: applyShader(HitRecord *rec) const
{
    QVector2D position(rec->uv.x() / brickSize.x(), rec->uv.y() / brickSize.y());
    if ((position.x() / 2 - floorf(position.x() / 2)) > 0.5)
        position.setY(position.y() + 0.5);

    position.setX(position.x() - floor(position.x()));
    position.setY(position.y() - floor(position.y()));

    bool useBrick = (position.x() < brickPct.x()) && (position.y() < brickPct.y());
    if (useBrick)
        return brickShader->applyShader(rec);
    return mortarShader->applyShader(rec);
}

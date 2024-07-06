#ifndef BRICKWALLSHADER_H
#define BRICKWALLSHADER_H

#include "shader.h"
#include <QVector2D>

struct BrickWallShader : public Shader
{
    const Shader *brickShader;
    const Shader *mortarShader;
    QVector2D brickSize;
    QVector2D brickPct;

    BrickWallShader(const Shader *_brickShader, const Shader *_mortarShader, QVector2D _brickSize, QVector2D _brickPct);
    RGBA applyShader(HitRecord *rec) const;

};

#endif // BRICKWALLSHADER_H

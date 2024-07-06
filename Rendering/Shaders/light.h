#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include "../Core/rgba.h"

struct Light
{
    QVector3D location;
    RGBA ambientColor;
    RGBA specularColor;
    RGBA diffuseColor;

    Light(const QVector3D &_location, const RGBA &_ambientColor,
          const RGBA &_specularColor, const RGBA &_diffuseColor)
        : location(_location), ambientColor(_ambientColor),
        specularColor(_specularColor), diffuseColor(_diffuseColor)
    {}
};


#endif // LIGHT_H

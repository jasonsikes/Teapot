#include "texture.h"
#include "../Objects/shape.h"


RGBA CheckerboardTexture :: applyTexture(HitRecord *rec) const
{
    const float checkSize = 1;
    int v = floorf(rec->uv.y() * vMult);
    int u = floorf(rec->uv.x() * uMult);
    if ((v + u) % 2 == 0) {
        return color1->applyTexture(rec);
    } else {
        return color2->applyTexture(rec);
    }
}



RGBA SwirlTexture :: applyTexture(HitRecord *rec) const
{
    float angle = atan2f(rec->uv.y() * vMult, rec->uv.x() * uMult);
    float t = (sinf(angle * 10) + 1) / 2;
    return color1->applyTexture(rec) * t + color2->applyTexture(rec) * (1 - t);
}


RGBA GradientTexture :: applyTexture(HitRecord *rec) const
{
    float t = fmodf(rec->uv.y() * vMult, 1.0f);
    if (t < 0) t += 1.0f;
    return color1->applyTexture(rec) * t + color2->applyTexture(rec) * (1 - t);
}

ImageTexture :: ImageTexture(QString filename)
{
    QString imagePath = QString(FIND_FILES) + "/" + filename;
    image = QImage(imagePath);
    if (image.isNull()) {
        qDebug() << "Failed to load image: " << imagePath;
    }
}

RGBA ImageTexture :: applyTexture(HitRecord *rec) const
{
    int x = (1.0f - rec->uv.x()) * image.width();
    int y = rec->uv.y() * image.height();
    QRgb pixel = image.pixel(x, y);
    return RGBA(qRed(pixel) / 255.0, qGreen(pixel) / 255.0, qBlue(pixel) / 255.0, 1);
}
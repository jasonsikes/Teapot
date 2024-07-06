#include "shader.h"
#include "../Objects/shape.h"


RGBA CheckerboardShader :: applyShader(HitRecord *rec) const
{
    const float checkSize = 1;
    int v = floorf(rec->uv.y() * vMult);
    int u = floorf(rec->uv.x() * uMult);
    if ((v + u) % 2 == 0) {
        return color1->applyShader(rec);
    } else {
        return color2->applyShader(rec);
    }
}



RGBA SwirlShader :: applyShader(HitRecord *rec) const
{
    float angle = atan2f(rec->uv.y() * vMult, rec->uv.x() * uMult);
    float t = (sinf(angle * 10) + 1) / 2;
    return color1->applyShader(rec) * t + color2->applyShader(rec) * (1 - t);
}


RGBA GradientShader :: applyShader(HitRecord *rec) const
{
    float t = fmodf(rec->uv.y() * vMult, 1.0f);
    if (t < 0) t += 1.0f;
    return color1->applyShader(rec) * t + color2->applyShader(rec) * (1 - t);
}

ImageShader :: ImageShader(QString filename)
{
    QString imagePath = QString(FIND_FILES) + "/" + filename;
    image = QImage(imagePath);
    if (image.isNull()) {
        qDebug() << "Failed to load image: " << imagePath;
    }
}

RGBA ImageShader :: applyShader(HitRecord *rec) const
{
    int x = (1.0f - rec->uv.x()) * image.width();
    int y = rec->uv.y() * image.height();
    QRgb pixel = image.pixel(x, y);
    return RGBA(qRed(pixel) / 255.0, qGreen(pixel) / 255.0, qBlue(pixel) / 255.0, 1);
}
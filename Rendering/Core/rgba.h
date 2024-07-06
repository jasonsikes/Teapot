#ifndef RGBA_H
#define RGBA_H

#include <QColor>
#include "QtCore/qdebug.h"

// The RGBA class represents a color.
// Each component (R, G, B, and A) is a float between 0 and 1.
struct RGBA {
    float r,g,b,a;

    RGBA() : r(0),g(0),b(0),a(0) {}
    RGBA(float aR, float aG, float aB, float aA = 1)
        : r(aR), g(aG), b(aB), a(aA) {}
    RGBA(const QColor &src)
    {
        r = src.redF();
        g = src.greenF();
        b = src.blueF();
        a = src.alphaF();
    }

    float value() const { return (r + g + b) * a / 3; }

    friend RGBA operator+(const RGBA& c1, const RGBA & c2);
    friend RGBA operator*(const RGBA& c1, const RGBA & c2);
    friend RGBA operator*(const RGBA& c, float f);
    friend RGBA operator*(float f, const RGBA & c);

    inline RGBA& operator+=(const RGBA & right_op) {
        *this = *this + right_op;
        return *this;
    }

    operator QString() const { return QString("[RGBA: %1, %2, %3, %4]").arg(r).arg(g).arg(b).arg(a); }
};

inline RGBA operator*(const RGBA & c, float f)
{ return RGBA(c.r * f, c.g * f, c.b * f, 1); }

inline RGBA operator*(float f, const RGBA & c)
{ return RGBA(c.r * f, c.g * f, c.b * f, 1); }

inline RGBA operator+(const RGBA & c1, const RGBA & c2)
{ return RGBA(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, 1); }

inline RGBA operator*(const RGBA & c1, const RGBA & c2)
{ return RGBA(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, 1); }


#endif // RGBA_H

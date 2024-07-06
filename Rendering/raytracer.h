#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Core/ray.h"
#include "Core/rgba.h"
#include <QVector4D>

class Scene;
class Shape;
class Light;

// The Raytracer class is used to render the scene.
// It is used to trace the rays from the camera to the scene.
struct Raytracer
{
    Scene *scene;
    Raytracer(Scene *aScene);

    // Return the color for normalized screen coordinates.
    RGBA rgbAtIJ(float i, float j);

    RGBA traceRay(Ray r, int depth, bool rayIsInside = false);

};

#endif // RAYTRACER_H

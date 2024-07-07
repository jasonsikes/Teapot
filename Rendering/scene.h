#ifndef SCENE_H
#define SCENE_H

#include "Core/camera.h"
#include <QColor>
#include "Textures/texture.h"
#include "Textures/shader.h"
#include "Textures/marbletexture.h"
#include "Textures/brickwalltexture.h"

class Shape;
class Light;
class Shader;

// The Scene class represents the scene to be rendered.
// It contains the camera, shapes, and lights in the scene.
struct Scene
{
    Scene();
    ~Scene();

    const float cameraXi1 = 0.5;
    const float cameraXi2 = 0.5;

    const RGBA black = {0.2,0.2,0.2,1};
    const RgbTexture blackTexture = black;

    const RGBA nothing = {0.0,0.0,0.0,1};
    const RgbTexture nothingTexture = nothing;

    const RGBA all = {1,1,1,1};
    const RgbTexture allTexture = all;

    const RGBA white = {0.8,0.8,0.8,1};
    const RgbTexture whiteTexture = white;

    const RGBA green = {0,0.7,0,1};
    const RgbTexture greenTexture = green;

    const RGBA red = {0.7,0,0,1};
    const RgbTexture redTexture = red;

    const RGBA yellow = {0.7,0.7,0,1};
    const RgbTexture yellowTexture = yellow;

    const RGBA purple = {0.7,0,0.7,1};
    const RgbTexture purpleTexture = purple;

    const RGBA blue = {0,0.0,0.7,1};
    const RgbTexture blueTexture = blue;

    const SwirlTexture whitePurpleSwirlTexture = {&purpleTexture, &whiteTexture, 3, 3};

    const RGBA marbleColor1 = {0.7,0.7, 0.0, 1};
    const RgbTexture marbleTexture1 = marbleColor1;

    const RGBA marbleColor2 = {0.7,0,0.7, 1};
    const RgbTexture marbleTexture2 = marbleColor2;

    const ImageTexture earthTexture = ImageTexture("earth_2k.jpg");

    const RGBA backgroundColor = {0,0.7,0.7, 1};

    PhongShader marbleShader = {20};
    PhongShader floorShader = {100};

    const CheckerboardTexture checkerboardTexture = {&blackTexture, &whiteTexture, 8, 6};
    const SwirlTexture swirlTexture = {&redTexture, &yellowTexture, 6, 3};
    const GradientTexture gradientTexture = {&greenTexture, &blueTexture, 5};

    const RGBA redBrick = {0.7, 0.15, 0, 1};
    const RgbTexture redBrickTexture = redBrick;

    const RGBA grayMortar = {0.8, 0.95, 0.9, 1};
    const RgbTexture grayMortarTexture = grayMortar;
    const RGBA darkMortar = {0.6, 0.75, 0.7, 1};
    const RgbTexture darkMortarTexture = darkMortar;
    const MarbleTexture shaderdMortarTexture = MarbleTexture(&grayMortarTexture, &darkMortarTexture, &grayMortarTexture, 20, 5, 8);
    BrickWallTexture brickTexture = BrickWallTexture(&redBrickTexture, &shaderdMortarTexture, QVector2D(.0025, .0075), QVector2D(0.8, 0.9));
    BrickWallTexture brickReflectionTexture = BrickWallTexture(&redBrickTexture, &nothingTexture, QVector2D(.0025, .0075), QVector2D(0.8, 0.9));


    Camera camera;

    QList<Shape *> shapes;
    QList<Light *> lights;

};


#endif // SCENE_H

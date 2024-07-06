#ifndef SCENE_H
#define SCENE_H

#include "Core/camera.h"
#include <QColor>
#include "Shaders/shader.h"
#include "Shaders/texture.h"
#include "Shaders/marbleshader.h"
#include "Shaders/brickwallshader.h"

class Shape;
class Light;
class Texture;

// The Scene class represents the scene to be rendered.
// It contains the camera, shapes, and lights in the scene.
struct Scene
{
    Scene();
    ~Scene();

    const float cameraXi1 = 0.5;
    const float cameraXi2 = 0.5;

    const RGBA black = {0.2,0.2,0.2,1};
    const RgbShader blackShader = black;

    const RGBA nothing = {0.0,0.0,0.0,1};
    const RgbShader nothingShader = nothing;

    const RGBA all = {1,1,1,1};
    const RgbShader allShader = all;

    const RGBA white = {0.8,0.8,0.8,1};
    const RgbShader whiteShader = white;

    const RGBA green = {0,0.7,0,1};
    const RgbShader greenShader = green;

    const RGBA red = {0.7,0,0,1};
    const RgbShader redShader = red;

    const RGBA yellow = {0.7,0.7,0,1};
    const RgbShader yellowShader = yellow;

    const RGBA purple = {0.7,0,0.7,1};
    const RgbShader purpleShader = purple;

    const RGBA blue = {0,0.0,0.7,1};
    const RgbShader blueShader = blue;

    const SwirlShader whitePurpleSwirlShader = {&purpleShader, &whiteShader, 3, 3};

    const RGBA marbleColor1 = {0.7,0.7, 0.0, 1};
    const RgbShader marbleShader1 = marbleColor1;

    const RGBA marbleColor2 = {0.7,0,0.7, 1};
    const RgbShader marbleShader2 = marbleColor2;

    const ImageShader earthShader = ImageShader("earth_2k.jpg");

    const RGBA backgroundColor = {0,0.7,0.7, 1};

    PhongTexture marbleTexture = {20};
    PhongTexture floorTexture = {100};

    const CheckerboardShader checkerboardShader = {&blackShader, &whiteShader, 8, 6};
    const SwirlShader swirlShader = {&redShader, &yellowShader, 6, 3};
    const GradientShader gradientShader = {&greenShader, &blueShader, 5};

    const RGBA redBrick = {0.7, 0.15, 0, 1};
    const RgbShader redBrickShader = redBrick;

    const RGBA grayMortar = {0.8, 0.95, 0.9, 1};
    const RgbShader grayMortarShader = grayMortar;
    const RGBA darkMortar = {0.6, 0.75, 0.7, 1};
    const RgbShader darkMortarShader = darkMortar;
    const MarbleShader texturedMortarShader = MarbleShader(&grayMortarShader, &darkMortarShader, &grayMortarShader, 20, 5, 8);
    BrickWallShader brickShader = BrickWallShader(&redBrickShader, &texturedMortarShader, QVector2D(.0025, .0075), QVector2D(0.8, 0.9));
    BrickWallShader brickReflectionShader = BrickWallShader(&redBrickShader, &nothingShader, QVector2D(.0025, .0075), QVector2D(0.8, 0.9));


    Camera camera;

    QList<Shape *> shapes;
    QList<Light *> lights;

};


#endif // SCENE_H

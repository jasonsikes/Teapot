#include "scene.h"
#include "Objects/sphere.h"
#include "Objects/plane.h"
#include "Objects/triangle.h"
#include "Objects/trianglegroup.h"
#include "Shaders/light.h"
#include "trianglereader.h"


Scene::Scene() {

    Sphere *yellowCenterMarble = new Sphere(
        {-1.02,.02,.52},
        {0,1,0},
        1,
        &marbleTexture,
        &marbleShader1,
        &whiteShader,
        1.5,
        &nothingShader
        );


    Sphere *purpleBehindMarble = new Sphere(
        {1.02,.02,.52},
        {0,1,0},
        1,
        &marbleTexture,
        &marbleShader2,
        &whiteShader,
        1.5,
        &nothingShader
        );

    // New Spheres with interesting patterns
    Sphere *checkerboardSphere = new Sphere(
        {-1, .02, -18},
        {1, .33, 0},
        1,
        &marbleTexture,
        &checkerboardShader,
        &nothingShader,
        1.5,
        &nothingShader
        );

    Sphere *earthSphere = new Sphere(
        {-14.04, 1.02, -5},
        {0.75, 0.25, .25},
        3,
        &marbleTexture,
        &earthShader,
        &nothingShader,
        1.5,
        &nothingShader
        );

    Sphere *swirlSphere = new Sphere(
        {-2, .02, -12},
        {1, 0, 0},
        1,
        &marbleTexture,
        &swirlShader,
        &nothingShader,
        1.5,
        &nothingShader
        );

    Sphere *gradientSphere = new Sphere(
        {-5.04,0.02,-14},
        {0.1, 0.4, 1},
        1,
        &marbleTexture,
        &gradientShader,
        &nothingShader,
        1.5,
        &nothingShader
        );

    Sphere *crystalSphere = new Sphere(
        {1.42, .02, -6.0},
        {0, 1, 0},
        1,
        &marbleTexture,
        &blackShader,
        &nothingShader,
        1.5,
        &allShader
        );

    Water *water = new Water(
        {1,0,0},
        {0,0,1},
        {0, -1.6, 0},
        &floorTexture,
        &blueShader,
        &whiteShader,
        1,
        &nothingShader
        );


    float th = -0.9;
    float tl = -9;
    float tr = 9;
    float tn = 2.3;
    float tf = -22;

    const QVector3D table_p0(tl,th,tf);

    const QVector3D table_p1(tl,th,tn);
    const QVector3D table_p2(tr,th,tn);

    const QVector3D table_p3(tr,th,tf);

    const QVector3D table_p4(tr,tf,tn);
    const QVector3D table_p5(tl,tf,tn);

    float ttv = 0.072;
    float ttu = 0.0735;

    const QVector2D table_t0(0,0);
    const QVector2D table_t1(ttv,0);
    const QVector2D table_t2(ttv,ttu);
    const QVector2D table_t3(0,ttu);

    const Texture &tableTexture = floorTexture;
    const Shader &tableShader = brickShader;
    const Shader &tableReflection = brickReflectionShader;
    float tableRefraction = 1;
    const Shader &tableTransparency = nothingShader;

    Triangle *table1 = new Triangle(table_p0, table_p1, table_p2,
                                    table_t0, table_t1, table_t2,
                                    &tableTexture, &tableShader, &tableReflection,
                                    tableRefraction, &tableTransparency);
    Triangle *table2 = new Triangle(table_p0, table_p2, table_p3,
                                    table_t0, table_t2, table_t3,
                                    &tableTexture, &tableShader, &tableReflection,
                                    tableRefraction, &tableTransparency);
    Triangle *table3 = new Triangle(table_p1, table_p4, table_p2,
                                    table_t1, table_t3, table_t2,
                                    &tableTexture, &tableShader, &tableReflection,
                                    tableRefraction, &tableTransparency);
    Triangle *table4 = new Triangle(table_p1, table_p5, table_p4,
                                    table_t1, table_t0, table_t3,
                                    &tableTexture, &tableShader, &tableReflection,
                                    tableRefraction, &tableTransparency);



    lights.push_back(new Light(QVector3D(-60,120,70),
                               RGBA(0.1, 0.1, 0.1, 1),
                               RGBA(0.3, 0.3, 0.3, 1),
                               RGBA(0.5, 0.5, 0.3, 1)));

    lights.push_back(new Light(QVector3D(70,120,70),
                               RGBA(0.1, 0.1, 0.1, 1),
                               RGBA(0.3, 0.3, 0.3, 1),
                               RGBA(0.3, 0.3, 0.5, 1)));

    lights.push_back(new Light(QVector3D(-30,50,-80),
                               RGBA(0, 0, 0.1, 1),
                               RGBA(0.3, 0.1, 0, 1),
                               RGBA(0, 0, 0, 1)));



    shapes.push_back(yellowCenterMarble);
    shapes.push_back(purpleBehindMarble);
    shapes.push_back(crystalSphere);
    shapes.push_back(checkerboardSphere);
    shapes.push_back(swirlSphere);
    shapes.push_back(gradientSphere);
    shapes.push_back(earthSphere);
    shapes.push_back(water);
    shapes.push_back(table1);
    shapes.push_back(table2);
    shapes.push_back(table3);
    shapes.push_back(table4);

    float whRatio = 1920.0f / 1080.0f;

    // Camera parameters
    QVector3D center(5,5,18);
    QVector3D vup(0,1,0);
    QVector3D gaze(-0.31,-.35,-1);
    float imageTop = 1;
    float imageRight = imageTop * whRatio;
    float imageDistance = 3;
    float imageAperture = 1;

    float imageLeft = -imageRight;
    float imageBottom = -imageTop;

    camera = {center, gaze, vup, imageAperture, imageLeft,
              imageRight, imageBottom, imageTop, imageDistance};

    TriangleReader reader;

    // The Utah Teapot
    reader.texture = &marbleTexture;
    reader.shader = &whitePurpleSwirlShader;
    reader.reflection = &blackShader;
    reader.transparency = &nothingShader;
    reader.indexOfRefraction = 1.02;
    reader.scale = {1,1,1};
    reader.translation = {-5, -0.97, 0};
    QList<QList<Triangle> > teapot = reader.readTriangles("teapot_surface0.norm");
    for (auto &t : teapot)
        shapes.push_back(new TriangleGroup(t));

    // The Stanford Bunny
    reader.texture = &marbleTexture;
    reader.shader = &blueShader;
    reader.reflection = &blackShader;
    reader.transparency = &nothingShader;
    reader.indexOfRefraction = 1.2;
    reader.scale = {5, 5, 5};
    reader.translation = {5.5, 1.55, -1};
    QList<QList<Triangle> > bunny = reader.readTriangles("bunny_surface0.norm");
    for (auto &t : bunny)
        shapes.push_back(new TriangleGroup(t));

}

Scene::~Scene()
{
    for (auto s : shapes)
        delete s;
    for (auto s : lights)
        delete s;
}
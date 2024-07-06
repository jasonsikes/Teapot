#ifndef TRIANGLEREADER_H
#define TRIANGLEREADER_H

#include "Objects/triangle.h"
#include <QList>
#include <QTextStream>

// The TriangleReader class is used to read the triangles from the given source file and
// divide the triangles into groups.
class TriangleReader
{
    // The maximum triangles per group. An arbitrarily-chosen number.
    int tMax = 60;

    QList<Triangle> biglist;
    QTextStream *readStream;
    
    Triangle readTriangle();
    QVector3D readVector3D();
    QList<QVector3D> calculateMinMax(QList<Triangle> triangles);

    // Translate all of the triangles in the list by the translation vector
    // (which should be set before calling this function).
    void translate();

    // Scale all of the triangles in the list by the translation vector
    // (which should be set before calling this function).
    void scaleVertices();

    // Calculate the UV coordinates for each vertex of each triangle in the list.
    void calculateUVs();

    // The min and max of the x,y,z vertices of the whole object.
    QVector3D objectMax;
    QVector3D objectMin;

    // Given a point and the center of the object, calculate the UV coordinates for that point.
    QVector2D calculateUV(QVector3D point, QVector3D center);

    // Divide the list of triangles into two lists of triangles.
    QList<QList<Triangle> >split(QList<Triangle> triangles);

    // Recursively subdivide the triangle groups.
    QList<QList<Triangle> > subdivide(QList<Triangle> triangles);

public:

    // SET THESE VALUES BEFORE CALLING readTriangles()!!!
    const Texture *texture;
    const Shader *shader;
    const Shader *reflection;
    float indexOfRefraction;
    const Shader *transparency;
    QVector3D translation;
    QVector3D scale;

    TriangleReader();
    QList<QList<Triangle> > readTriangles(QString filePath);

};

#endif // TRIANGLEREADER_H

#include "trianglereader.h"
#include <QFile>
#include <QDebug>
#include <QDir>

TriangleReader::TriangleReader() {}

QList<QList<Triangle> > TriangleReader::readTriangles(QString filePath) {
    QFile file(filePath);
    if ( ! file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file" << filePath;
        qDebug() <<"Searched for file in" << QDir::currentPath();
        return QList<QList<Triangle> >();
    }

    QTextStream inStream(&file);
    readStream = &inStream;

    // First line is the count of triangles
    int numTriangles = readStream->readLine().toInt();

    // Read in the big list of triangles.
    biglist.clear();
    for (int i = 0; i < numTriangles; i++) {
        biglist.append(readTriangle());
    }

    QList<QVector3D> minMax = calculateMinMax(biglist);
    objectMax = minMax[0];
    objectMin = minMax[1];

    calculateUVs();

    scaleVertices();
    translate();

    QList<QList<Triangle> > retval = subdivide(biglist);

    return retval;
}

// Reads a single triangle from the stream. The format is:
// 3 vertices, 3 normals, interlaced.
// The vertices are in the format {x, y, z}, the normals are in the format {x, y, z}.
// The normals may not be normalized.
Triangle TriangleReader::readTriangle() {
    // A temporary texture uv coordinate. We will calculate it later.
    static QVector2D tempUV = QVector2D(0, 0);
    QVector3D v1 = readVector3D();
    QVector3D n1 = readVector3D();
    QVector3D v2 = readVector3D();
    QVector3D n2 = readVector3D();
    QVector3D v3 = readVector3D();
    QVector3D n3 = readVector3D();

    // Read the spacer line.
    readStream->readLine();

    return Triangle(v1, v2, v3,
                   tempUV, tempUV, tempUV,
                   n1, n2, n3,
                   texture, shader, reflection, indexOfRefraction, transparency);
}


QVector3D TriangleReader::readVector3D() {
    QString line = readStream->readLine();
    QStringList parts = line.split(' ');
    return QVector3D(parts[0].toFloat(), parts[1].toFloat(), parts[2].toFloat());
}


void TriangleReader::translate() {
    for (Triangle &triangle : biglist) {
        triangle.p0 += translation;
        triangle.p1 += translation;
        triangle.p2 += translation;
    }
}

void TriangleReader::scaleVertices() {
    for (Triangle &triangle : biglist) {
        triangle.p0 *= scale;
        triangle.p1 *= scale;
        triangle.p2 *= scale;
    }
}

    // Calculate the max,min of each vertex of each triangle.
QList<QVector3D> TriangleReader::calculateMinMax(QList<Triangle> triangles) {
    QVector3D max = triangles[0].p0;
    QVector3D min = triangles[0].p0;
    for (auto &t : triangles) {
        if (t.p0.x() > max.x()) max.setX(t.p0.x());
        if (t.p0.y() > max.y()) max.setY(t.p0.y());
        if (t.p0.z() > max.z()) max.setZ(t.p0.z());
        if (t.p0.x() < min.x()) min.setX(t.p0.x());
        if (t.p0.y() < min.y()) min.setY(t.p0.y());
        if (t.p0.z() < min.z()) min.setZ(t.p0.z());
    }
    return {min,max};
}

// Split the list of triangles in half, using the widest dimension of the bounding box.
QList<QList<Triangle> > TriangleReader::split(QList<Triangle> triangles) {
    QList<QVector3D> minMax = calculateMinMax(triangles);
    QVector3D min = minMax[0];
    QVector3D max = minMax[1];

    // Calculate the longest dimension.
    QVector3D longest = max - min;
    int dimension = 0;
    // Calculate the longest dimension.
    if (longest.y() > longest.x()) dimension = 1;
    if (longest.z() > longest.x() && longest.z() > longest.y()) dimension = 2;

    // Sort the triangles by the average of the longest dimension.
    std::sort(triangles.begin(), triangles.end(), [&](const Triangle &a, const Triangle &b) {
        return (a.p0[dimension] + a.p1[dimension] + a.p2[dimension]) < (b.p0[dimension] + b.p1[dimension] + b.p2[dimension]);
    });

    int half = triangles.size() / 2;
    QList<Triangle> list1 = triangles.mid(0, half);
    QList<Triangle> list2 = triangles.mid(half);

    return {list1, list2};
}

// Recursively subdivide the triangle groups.
QList<QList<Triangle> > TriangleReader::subdivide(QList<Triangle> triangleGroup)
{
    if (triangleGroup.size() < tMax) {
        return {triangleGroup};
    }

    QList<QList<Triangle> > retval;
    QList<QList<Triangle> > i2 = split(triangleGroup);
    for (auto &group : i2) {
        if (group.size() > 0)
            retval.append(subdivide(group));
    }
    return retval;
}

// Calculate the UV coordinates for each vertex of each triangle in the list.
void TriangleReader::calculateUVs() {
    QVector3D center = (objectMax + objectMin) / 2.0f;
    for (auto &t : biglist) {
        
        t.t0 = calculateUV(t.p0, center);
        t.t1 = calculateUV(t.p1, center);
        t.t2 = calculateUV(t.p2, center);
    }
}

QVector2D TriangleReader::calculateUV(QVector3D point, QVector3D center) {
    float lon = atan2f(point.x() - center.x(), point.z() - center.z());
    float lat = atan2f(point.y() - center.y(), point.z() - center.z());
    return QVector2D(lon / (2 * M_PI) + 0.5, lat / M_PI + 0.5);
}

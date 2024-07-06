#include "solidnoise.h"
#include <sys/time.h>
#include "../Core/rng.h"

SolidNoise::SolidNoise()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    RNG random(tv.tv_usec);

    int i;

    grad[0] = QVector3D( 1, 1, 0);
    grad[1] = QVector3D(-1, 1, 0);
    grad[2] = QVector3D( 1,-1, 0);
    grad[3] = QVector3D(-1,-1, 0);

    grad[4] = QVector3D( 1, 0, 1);
    grad[5] = QVector3D(-1, 0, 1);
    grad[6] = QVector3D( 1, 0,-1);
    grad[7] = QVector3D(-1, 0,-1);

    grad[8] = QVector3D( 0, 1, 1);
    grad[9] = QVector3D( 0,-1, 1);
    grad[10]= QVector3D( 0, 1,-1);
    grad[11]= QVector3D( 0,-1,-1);

    grad[12]= QVector3D( 1, 1, 0);
    grad[13]= QVector3D(-1, 1, 0);
    grad[14]= QVector3D( 0,-1, 1);
    grad[15]= QVector3D( 0,-1,-1);

    for (i = 0; i < 16; i++)
        phi[i] = i;

    // shuffle phi
    for (i = 14; i >= 0; i--) {
        int target = int(random()*i);
        int temp = phi[i+1];
        phi[i+1] = phi[target];
        phi[target] = temp;
    }
}

SolidNoise::SolidNoise(int seed)
{
    RNG random(seed);

    int i;

    grad[0] = QVector3D( 1, 1, 0);
    grad[1] = QVector3D(-1, 1, 0);
    grad[2] = QVector3D( 1,-1, 0);
    grad[3] = QVector3D(-1,-1, 0);

    grad[4] = QVector3D( 1, 0, 1);
    grad[5] = QVector3D(-1, 0, 1);
    grad[6] = QVector3D( 1, 0,-1);
    grad[7] = QVector3D(-1, 0,-1);

    grad[8] = QVector3D( 0, 1, 1);
    grad[9] = QVector3D( 0,-1, 1);
    grad[10]= QVector3D( 0, 1,-1);
    grad[11]= QVector3D( 0,-1,-1);

    grad[12]= QVector3D( 1, 1, 0);
    grad[13]= QVector3D(-1, 1, 0);
    grad[14]= QVector3D( 0,-1, 1);
    grad[15]= QVector3D( 0,-1,-1);

    for (i = 0; i < 16; i++)
        phi[i] = i;

    // shuffle phi
    for (i = 14; i >= 0; i--) {
        int target = int(random()*i);
        int temp = phi[i+1];
        phi[i+1] = phi[target];
        phi[target] = temp;
    }
}


float SolidNoise::turbulence(const QVector3D& p, int depth)
    const
{
    float sum = 0.0f;
    float weight = 1.0f;
    QVector3D ptemp(p);

    sum = fabsf(noise(ptemp));

    for (int i = 1; i < depth; i++)
    {
        weight = weight * 2;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);

        sum += fabsf(noise(ptemp)) / weight;
    }
    return sum;
}

float SolidNoise::dturbulence(const QVector3D& p, int depth, float d)
    const {
    float sum = 0.0f;
    float weight = 1.0f;
    QVector3D ptemp(p);

    sum += fabsf(noise(ptemp)) / d;

    for (int i = 1; i < depth; i++)
    {
        weight = weight * d;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);

        sum += fabsf(noise(ptemp)) / d;
    }
    return sum;
}

QVector3D SolidNoise::vectorTurbulence(const QVector3D& p, int depth)
    const {
    QVector3D sum(0.0, 0.0, 0.0);
    QVector3D ptemp = p + QVector3D(5.1, 56.2, 25.8);
    float amp = 1.0;
    QVector3D off(0.321, 0.112, 0.724);

    for (int i = 0; i < depth; i++)
    {
        sum += vectorNoise(ptemp) * amp;
        amp = amp * 0.6;
        ptemp.setX( ptemp.x() * 2 + off.x() );
        ptemp.setY( ptemp.y() * 2 + off.y() );
        ptemp.setZ( ptemp.z() * 2 + off.z() );
    }
    return sum;
}

QVector3D SolidNoise::vectorNoise(const QVector3D& p) const {
    int i, j, k;
    int fi, fj, fk;
    QVector3D sum, v;

    sum = QVector3D(0.0, 0.0, 0.0);
    fi = int(floor(p.x()));
    fj = int(floor(p.y()));
    fk = int(floor(p.z()));
    for (i = fi; i <= fi+1; i++)
        for (j = fj; j <= fj+1; j++)
            for (k = fk; k <= fk+1; k++) {
                v = QVector3D(p.x() - i, p.y() - j, p.z() - k);
                sum += vectorKnot(i, j, k, v);
            }
    return sum;

}

float SolidNoise::noise(const QVector3D& p) const {
    int fi, fj, fk;
    float fu, fv, fw, sum;
    QVector3D v;

    fi = int(floorf(p.x()));
    fj = int(floorf(p.y()));
    fk = int(floorf(p.z()));
    fu = p.x() - float(fi);
    fv = p.y() - float(fj);
    fw = p.z() - float(fk);
    sum = 0.0;

    v = QVector3D(fu, fv, fw);
    sum += knot(fi, fj, fk, v);

    v = QVector3D(fu - 1, fv, fw);
    sum += knot(fi + 1, fj, fk, v);

    v = QVector3D(fu, fv - 1, fw);
    sum += knot(fi, fj + 1, fk, v);

    v = QVector3D(fu, fv, fw -1);
    sum += knot(fi, fj, fk + 1, v);

    v = QVector3D(fu -1, fv -1, fw);
    sum += knot(fi + 1, fj + 1, fk, v);

    v = QVector3D(fu -1, fv, fw -1);
    sum += knot(fi + 1, fj, fk + 1, v);

    v = QVector3D(fu, fv -1, fw -1);
    sum += knot(fi, fj + 1, fk + 1, v);

    v = QVector3D(fu -1, fv -1, fw -1);
    sum += knot(fi + 1, fj + 1, fk + 1, v);

    return sum;

}

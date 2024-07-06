#include "rendermain.h"
#include <QImage>
#include <QVector4D>
#include "Rendering/raytracer.h"
#include "Rendering/Core/rng.h"


const int RANDOM_SAMPLES_PER_PIXEL = 11;


RenderMain::RenderMain(QImage *aRenderDestination, QObject *parent)
    : QObject{parent}, canvas(aRenderDestination)
{
    raytracer = new Raytracer(&scene);
}

void RenderMain::beginRendering() {
    countOfRowsRemaining = canvas->height();

    emit setProgressRangeSignal(0, countOfRowsRemaining);
    emit updateProgressSignal(0);

    // Having only one thread simplifies debugging.
    //QThreadPool::globalInstance()->setMaxThreadCount(1);

    for (int row = 0; row < countOfRowsRemaining; ++row) {
        Worker *worker = new Worker(row, canvas, raytracer, this);
        workers.push_back(worker);
        connect(worker, &Worker::taskCompleted, this, &RenderMain::taskFinished);
        RenderTask *task = new RenderTask(worker);
        QThreadPool::globalInstance()->start(task);
    }
}

void RenderMain::requestRenderPixel(QPoint p)
{
    float fRow = 1.0f - (float) p.y() / canvas->height();
    float fCol = (float) p.x() / canvas->width();
    RGBA sum = raytracer->rgbAtIJ(fCol, fRow);
    qDebug() <<sum;
}


void RenderMain::taskFinished(int row) {
    --countOfRowsRemaining;
    emit updateProgressSignal(canvas->height() - countOfRowsRemaining);
    emit updateRenderViewSignal();
    if (countOfRowsRemaining <= 0)
        endRendering();

}

void RenderMain::cancelRendering() {
    QThreadPool::globalInstance()->clear();
    QThreadPool::globalInstance()->waitForDone();
    emit renderingHasEndedSignal();
}


void RenderMain::endRendering() {
    for (Worker *worker : workers) {
        worker->deleteLater();
    }
    workers.clear();
    QThreadPool::globalInstance()->waitForDone();
    emit renderingHasEndedSignal();
}

void Worker::renderRow()
{
    RNG rng(row * 2);
    int rowCount = canvas->height();
    int colCount = canvas->width();
    float dRow = 1.0f - (float)row / rowCount;
    float vertPixelSize = 1.0f / rowCount;
    float horzPixelSize = 1.0f / colCount;
    for (int col = 0; col < colCount; ++col)
    {
        float dCol = (float)col / colCount;
        RGBA sum(0,0,0,0);
        for (int i = 0; i < RANDOM_SAMPLES_PER_PIXEL; ++i) {
            float rowVariance = dRow + (rng() - 0.5f) * vertPixelSize;
            float colVariance = dCol + (rng() - 0.5f) * horzPixelSize;
            sum += raytracer->rgbAtIJ(colVariance, rowVariance);
        }
        sum = sum * (1.0f / RANDOM_SAMPLES_PER_PIXEL);
        QColor c = QColor::fromRgbF(sum.r,sum.g,sum.b);
        canvas->setPixelColor(col, row, c);
    }
    emit taskCompleted(row);
}




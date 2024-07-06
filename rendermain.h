#ifndef RENDERMAIN_H
#define RENDERMAIN_H

#include <QObject>
#include <QThread>
#include <QThreadPool>
#include "Rendering/scene.h"
#include "Rendering/raytracer.h"

class Worker;

// The RenderMain class is the main controller for the rendering process.
class RenderMain : public QObject
{
    Q_OBJECT

    QImage *canvas;
    Scene scene;
    Raytracer *raytracer;

    QList<Worker*> workers;

    int countOfRowsRemaining;

public:
    explicit RenderMain(QImage *aRenderDestination, QObject *parent);

    void beginRendering();
    void cancelRendering();

signals:
    void renderingHasEndedSignal();

    void renderRowSignal(int aRow);

    void updateRenderViewSignal();

    void setProgressRangeSignal(int min, int max);
    void updateProgressSignal(int value);

public slots:

    // Called by MainWindow
    void endRendering();

    void taskFinished(int row);

    void requestRenderPixel(QPoint p);
};

// The Worker class is a worker thread for the rendering process.
// Each Worker instance is responsible for rendering a single row of pixels.
class Worker : public QObject {
    Q_OBJECT

    int row;
    QImage *canvas;
    Raytracer *raytracer;

public:
    explicit Worker(int aRow, QImage *aCanvas, Raytracer *aRaytracer, QObject *parent = nullptr)
        : QObject(parent), row(aRow), canvas(aCanvas), raytracer(aRaytracer) {}

    void renderRow();

    ~Worker()
    {

    }
signals:
    void taskCompleted(int row);
};


// The RenderTask is a task for the thread pool which owns the Worker thread that renders a row.
class RenderTask : public QRunnable {
    Worker* worker;

public:
    RenderTask(Worker* aWorker)
        : worker(aWorker) {
        this->setAutoDelete(false);
    }
    void run() override {
        worker->renderRow();
    }
};


#endif // RENDERMAIN_H

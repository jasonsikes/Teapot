#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include <QWidget>
#include <QImage>

// The RenderView widget displays the rendered image.
class RenderView : public QWidget
{
    Q_OBJECT

    // Set to true when rendering has begun.
    bool hasStartedRendering = false;

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

public:
    explicit RenderView(QWidget *parent = nullptr);

    // Call this to kick off the renderer.
    void beginRendering();

    // Rendering goes directly into the image.
    QImage image;


signals:
    void renderPixelRequestedSignal(QPoint p);
    void newHeightSignal(int);

public slots:
    void update();

};

#endif // RENDERVIEW_H

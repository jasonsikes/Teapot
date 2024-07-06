#include "renderview.h"
#include <QPainter>
#include <QMouseEvent>

RenderView::RenderView(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);
}


void RenderView::paintEvent(QPaintEvent *event)
{
    QPainter painter = QPainter(this);

    if (hasStartedRendering) {
        QSize scaledSize = image.size();
        scaledSize.scale(rect().size(), Qt::KeepAspectRatio);
        QRect centeredRect((rect().width() - scaledSize.width()) / 2,
                           (rect().height() - scaledSize.height()) / 2,
                           scaledSize.width(), scaledSize.height());
        painter.drawImage(centeredRect, image);
    }else {
        QPoint labelPosition = { size().width() / 2, size().height() / 2};
        painter.drawText(labelPosition, "Press 'Begin'");
    }
    painter.end();
}

void RenderView::mousePressEvent(QMouseEvent *event)
{
    if (hasStartedRendering) {
        QSize scaledSize = image.size();
        scaledSize.scale(rect().size(), Qt::KeepAspectRatio);
        QRect centeredRect((rect().width() - scaledSize.width()) / 2,
                           (rect().height() - scaledSize.height()) / 2,
                           scaledSize.width(), scaledSize.height());

        if (centeredRect.contains(event->position().x(), event->position().y())) {
            QPoint imagePos = event->pos() - centeredRect.topLeft();
            float xRatio = float(imagePos.x()) / centeredRect.width();
            float yRatio = float(imagePos.y()) / centeredRect.height();
            QPoint mappedPos(xRatio * image.width(), yRatio * image.height());
            qDebug() << "Mapped position in image:" << mappedPos;
            emit renderPixelRequestedSignal(mappedPos);
        }
    }

}


void RenderView::beginRendering()
{
    hasStartedRendering = true;
    update();
}


void RenderView::update()
{
    QWidget::update();
}


void RenderView::resizeEvent(QResizeEvent *event)
{
    int newHeight = rect().height();
    emit newHeightSignal(newHeight);
    QWidget::resizeEvent(event);
}

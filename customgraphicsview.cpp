#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal currentScale = transform().m11();

    if (event->delta() > 0 && currentScale < 100.0) {
        scale(scaleFactor, scaleFactor);
    } else if (currentScale > 0.5) {
        scale(1/scaleFactor, 1/scaleFactor);
    }
    setSceneRect(0, 0, width, height);
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::MidButton)
    {
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::MidButton)
    {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::MouseButton::MidButton)
    {
        setTransformationAnchor(QGraphicsView::NoAnchor);
        QPointF oldPos = mapToScene(lastMousePos);
        QPointF newPos = mapToScene(event->pos());
        QPointF deltaVec = newPos - oldPos;
        translate(deltaVec.x(), deltaVec.y());
        setSceneRect(0, 0, width, height);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }
    lastMousePos = event->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    setSceneRect(0, 0, width, height);
    QGraphicsView::resizeEvent(event);
}

void CustomGraphicsView::setHeight(qreal newHeight)
{
    height = newHeight;
}

void CustomGraphicsView::setWidth(qreal newWidth)
{
    width = newWidth;
}

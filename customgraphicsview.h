#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
class CustomGraphicsView : public QGraphicsView
{
public:
    CustomGraphicsView(QWidget* parent = 0);

    void setWidth(qreal newWidth);

    void setHeight(qreal newHeight);

protected:
     void wheelEvent(QWheelEvent *event) override;
     void mousePressEvent(QMouseEvent *event) override;
     void mouseReleaseEvent(QMouseEvent *event) override;
     void mouseMoveEvent(QMouseEvent *event) override;
     void resizeEvent(QResizeEvent *event) override;
private:
    const double scaleFactor = 1.2;
    QPoint lastMousePos = QPoint(0,0);
    qreal width = 0;
    qreal height = 0;
};

#endif // CUSTOMGRAPHICSVIEW_H

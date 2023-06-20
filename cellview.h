#ifndef CELLVIEW_H
#define CELLVIEW_H
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
class CellView : public QGraphicsObject
{
    Q_OBJECT
signals:
   void cellSelectedAsBlocked(int row, int col);
   void cellSelectedAsPoint(int row, int col);
public:
    CellView(qreal xPos, qreal yPos, qreal size, int id, int row, int col);
    bool getBlocked() const;
    void changeBlocked();
    const QList<CellView *> &getNeighbors() const;
    void setNeighbors(const QList<CellView *> &newNeighbors);
    QPointF getCentralCoords();

    bool getMarkedAsStartPoint() const;
    void setMarkedAsStartPoint(bool newMarkedAsStartPoint);

    bool getMarkedAsDestinationPoint() const;
    void setMarkedAsDestinationPoint(bool newMarkedAsDestinationPoint);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *opt, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
   qreal xPos = 0;
   qreal yPos = 0;
   qreal size = 0;
   int id = 0;
   int row = 0;
   int col = 0;
   bool blocked = false;
   QList<CellView*> neighbors;
   bool markedAsStartPoint = false;
   bool markedAsDestinationPoint = false;
};

#endif // CELLVIEW_H

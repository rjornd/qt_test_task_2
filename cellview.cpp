#include "cellview.h"

CellView::CellView(qreal xPos, qreal yPos, qreal size, int id, int row, int col):
    xPos(xPos), yPos(yPos), size(size), id(id), row(row), col(col)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF CellView::boundingRect() const
{
    return QRectF(QPoint(xPos, yPos),QPoint(xPos+size, yPos+size));
}

void CellView::paint(QPainter *painter, const QStyleOptionGraphicsItem *opt, QWidget *widget)
{
    QPen pen = QPen();
    QBrush brush = QBrush(Qt::lightGray);
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    QFont font= QFont();
    font.setPointSize(8);
    painter->setFont(font);
    if(blocked) painter->setBrush(brush);
    painter->drawRect(QRect(QPoint(xPos, yPos), QPoint(xPos+size, yPos+size)));
    pen.setColor(Qt::red);
    painter->setPen(pen);
    if(markedAsStartPoint) painter->drawText(getCentralCoords(), "A");
    if(markedAsDestinationPoint) painter->drawText(getCentralCoords(), "B");
    Q_UNUSED(opt);
    Q_UNUSED(widget);
}

void CellView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        emit CellView::cellSelectedAsBlocked(row, col);
    }

    if (event->button() == Qt::LeftButton) {
        emit CellView::cellSelectedAsPoint(row, col);
    }


    QGraphicsItem::mousePressEvent(event);
}

bool CellView::getMarkedAsDestinationPoint() const
{
    return markedAsDestinationPoint;
}

void CellView::setMarkedAsDestinationPoint(bool newMarkedAsDestinationPoint)
{
    markedAsDestinationPoint = newMarkedAsDestinationPoint;
    update();
}

bool CellView::getMarkedAsStartPoint() const
{
    return markedAsStartPoint;
}

void CellView::setMarkedAsStartPoint(bool newMarkedAsStartPoint)
{
    markedAsStartPoint = newMarkedAsStartPoint;
    update();
}

const QList<CellView *> &CellView::getNeighbors() const
{
    return neighbors;
}

void CellView::setNeighbors(const QList<CellView *> &newNeighbors)
{
    neighbors = newNeighbors;
}

QPointF CellView::getCentralCoords()
{
    return QPointF(xPos + size / 2, yPos + size / 2);
}


bool CellView::getBlocked() const
{
    return blocked;
}

void CellView::changeBlocked()
{
    blocked = !blocked;
}

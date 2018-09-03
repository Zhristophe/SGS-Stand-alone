#include "carditem.h"
#include <QPainter>
#include <QDebug>

CardItem::CardItem(Card *card)
    : m_width(46), m_height(75),
      m_index(-1)
{
    m_card = card;
    setAcceptHoverEvents(true);
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush;
    brush.setColor(Qt::yellow);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setBrush(brush);

    painter->drawRect(boundingRect());
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit enterHover();
    emit enterHover(m_index);
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit leaveHover();
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

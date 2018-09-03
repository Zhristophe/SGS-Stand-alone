#include "button.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

Button::Button(const QString &text)
    : m_width(100), m_height(62), text(text)
{
    setAcceptHoverEvents(true);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), text);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void Button::resize(QSizeF size)
{
    m_width = size.width();
    m_height = size.height();
}

void Button::resize(qreal w, qreal h)
{
    m_width = w;
    m_height = h;
}

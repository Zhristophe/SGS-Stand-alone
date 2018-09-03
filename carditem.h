#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Card;

class CardItem : public QGraphicsObject
{
    Q_OBJECT

public:
    CardItem(Card *card = nullptr);
    ~CardItem() {}

    QRectF boundingRect() const { return QRectF(-m_width / 2, -m_height / 2, m_width, m_height); }

    void setIndex(const int index) { m_index = index; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    int m_width, m_height;
    int m_index;

    Card *m_card;

signals:
    void enterHover();
    void enterHover(int);
    void leaveHover();
    void clicked();
};

#endif // CARDITEM_H


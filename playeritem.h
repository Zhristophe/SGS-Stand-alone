#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsObject>

class Player;

class PlayerItem : public QGraphicsObject
{
    Q_OBJECT

public:
    PlayerItem(Player *player);

    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;

    Player *m_player;
};

class PlayerShow : public QGraphicsObject
{
    Q_OBJECT

public:
    PlayerShow(Player *player);

    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;

    Player *m_player;
};

#endif // PLAYERITEM_H

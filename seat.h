#ifndef SEAT_H
#define SEAT_H

#include <QGraphicsObject>

class Player;
class PlayerItem;
class Button;

class RoomSeat : public QGraphicsObject
{
    Q_OBJECT

public:
    RoomSeat();

    QRectF boundingRect() const;
    bool isEmpty() const;
    bool seated(Player *player);

public slots:
    void createRobot();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

private:
    qreal m_width, m_height;
    Player *m_player;

    Button *addRobot;

signals:
    void enterHover();
    void leaveHover();
    void playerEnter(Player *);
};

class RoomSeatArea : public QGraphicsObject
{
    Q_OBJECT

public:
    RoomSeatArea(int numOfSeats = 8);

    QRectF boundingRect() const;
    void addSeat();
    bool addPlayer(Player *player);

    QList<Player *> getPlayers() const { return Players; }

public slots:
    void playerSeated(Player *player);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void adjustItems();

private:
    qreal m_width, m_height;

    QList<RoomSeat *> Seats;
    QList<Player *> Players;

    QPointF seatPos(int i, int n);
    qreal calSpace(qreal W, qreal w, int n) { return (W - n * w) / (n + 1); }

};

#endif // SEAT_H

#ifndef OPERATIONPANEL_H
#define OPERATIONPANEL_H

#include <QGraphicsObject>
#include "settings.h"

class Card;
class CardItem;
class Player;
class GameEvent;
class PlayerItem;

extern const qreal margin;
extern Player g_Player;

class OperationPanel : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(int numOfHandCards READ numOfHandCards)

public:
    OperationPanel(Player *owner = &g_Player);
    QRectF boundingRect() const;
    int numOfHandCards() const { return m_numOfHandCards; }

    QList<CardItem *> cardssss() const { return handCards; }

public slots:
    void addHandCard(Card *card);
    void addPlayer(Player *player);
    void reciveEvent(GameEvent *event);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;
    qreal leftOfEquipmentArea, rightOfEquipmentArea, heightOfEquipmentArea;
    qreal leftOfHandArea, rightOfHandArea, heightOfHandArea;

    QRectF baseRect, equipmentAreaRect, handAreaRect;

    QList<CardItem *> handCards;
    QList<int> index;
    QList<PlayerItem *> players;
    Player *m_owner;

    int m_numOfHandCards;

    void adjustHandCards();
    void adjustPlayers();

signals:
    void sendEvent(GameEvent *);
};

#endif // OPERATIONPANEL_H

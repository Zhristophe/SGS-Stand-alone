#include "operationpanel.h"
#include "carditem.h"
#include "player.h"
#include "playeritem.h"
#include <QPainter>
#include <QRectF>
#include <card.h>
#include "settings.h"

const qreal margin = 10;

OperationPanel::OperationPanel(Player *owner)
    : m_width(g_Config.value("SizeOfView").toSizeF().width()), m_height(g_Config.value("SizeOfView").toSizeF().height()),
      baseRect(QRectF(-m_width / 2, m_height / 2 - 200, 1000, 200)),
      equipmentAreaRect(QRectF(-m_width / 2, m_height / 2 - 150, 200, 150)),
      handAreaRect(QRectF(equipmentAreaRect.right(), equipmentAreaRect.top(), 800 - 124, 150))
{
    m_owner = owner;
}

QRectF OperationPanel::boundingRect() const
{
    QSizeF size = g_Config.value("SizeOfView").toSizeF();
    qreal x = -size.width() / 2;
    qreal y = -size.height() / 2;
//    qDebug() << QRectF(QPointF(x, y), size);
    return QRectF(QPointF(x, y), size);
}

void OperationPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(baseRect);
    painter->drawRect(equipmentAreaRect);
    painter->drawRect(handAreaRect);
}

void OperationPanel::addHandCard(Card *card)
{
    CardItem *cardItem = new CardItem(card);
    cardItem->setParentItem(this);
    cardItem->setIndex(m_numOfHandCards);
//    connect(cardItem, SIGNAL(enterHover(int)), this, SLOT(dd(int)));
    handCards.append(cardItem);
    index.append(m_numOfHandCards);
    ++m_numOfHandCards;
    adjustHandCards();
}

void OperationPanel::adjustHandCards()
{
    QPointF relativePos = QPointF(boundingRect().left() + leftOfHandArea + margin + 46 / 2,
                                  m_height / 2 - heightOfHandArea / 2);
    bool roomIsEnough = ((m_numOfHandCards * 46 + margin * 2) < (rightOfHandArea - leftOfHandArea));
    if (roomIsEnough) {
        for(int i = 0; i != m_numOfHandCards; ++i) {
            handCards.at(index.at(i))->setPos(relativePos);
            relativePos += QPointF(46, 0);
        }
    }
}

void OperationPanel::addPlayer(Player *player)
{
//    if (player->getId() == g_Config.value("id")) {
//        return;
//    }
    if (player->getId() == g_Player.getId()) {
        return;
    }
    PlayerItem *playerItem = new PlayerItem(player);
    playerItem->setParentItem(this);
    players.append(playerItem);
    adjustPlayers();
}

void OperationPanel::adjustPlayers()
{
    const int numOfPlayer = players.count();
    qDebug() << numOfPlayer;
    int b = numOfPlayer / 3 , a = numOfPlayer - b * 2;
    qreal W = m_width, H = m_height - baseRect.height();
    QSizeF size = g_Config.value("SizeOfPhoto").toSizeF();
    qreal w = size.width(), h = size.height();
    qreal xSpace = (W - margin * 2 - w * (a + 2)) / (a + 1), ySpace = (H - margin * 2 - h * b) / (b + 1);
    QRectF rect = boundingRect() - QMarginsF(0, 0, 0, 200);
    int n = 1;
    foreach (PlayerItem *playerItem, players) {
        if(n <= b)
            playerItem->setPos(QPointF(rect.right() - margin - w / 2, rect.bottom() - margin - (ySpace + h) * n + h / 2));
        else if (n <= a + b)
            playerItem->setPos(QPointF(rect.right() - margin - (xSpace + w) * (n - b) - w / 2, rect.top() + margin + h / 2));
        else
            playerItem->setPos(QPointF(rect.left() + margin + w / 2, rect.top() + margin + (ySpace + h) * (n - a - b) - h / 2));
        n++;
    }
}

void OperationPanel::reciveEvent(GameEvent *event)
{
    event = nullptr;
    addHandCard(new Card);
}

#include "playeritem.h"
#include "player.h"
#include "settings.h"
#include <QPainter>

PlayerItem::PlayerItem(Player *player)
    : m_width(g_Config.value("SizeOfPhoto").toSizeF().width()), m_height(g_Config.value("SizeOfPhoto").toSizeF().height())
{
    m_player = player;
}

QRectF PlayerItem::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void PlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

PlayerShow::PlayerShow(Player *player)
    : m_width(g_Config.value("SizeOfPhoto").toSizeF().width()), m_height(g_Config.value("SizeOfPhoto").toSizeF().height())
{
    m_player = player;
}

QRectF PlayerShow::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void PlayerShow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    painter->drawText(0, 0, m_player->getId());
}

#include "seat.h"
#include "settings.h"
#include "playeritem.h"
#include <QPainter>
#include "button.h"
#include "player.h"
#include <QTime>

RoomSeat::RoomSeat()
    : m_width(g_Config.value("SizeOfPhoto").toSizeF().width()), m_height(g_Config.value("SizeOfPhoto").toSizeF().height()),
      m_player(nullptr)
{
    setAcceptHoverEvents(true);

    addRobot = new Button("add a robot");
    addRobot->resize(100, 20);
    addRobot->setPos(0, 60);
    addRobot->setParentItem(this);
    addRobot->hide();
    connect(this, SIGNAL(enterHover()), addRobot, SLOT(slotShow()));
    connect(this, SIGNAL(leaveHover()), addRobot, SLOT(slotHide()));
    connect(addRobot, SIGNAL(clicked()), this, SLOT(createRobot()));
}

bool RoomSeat::isEmpty() const
{
    return (m_player == nullptr);
}

bool RoomSeat::seated(Player *player)
{
    if (m_player != nullptr) {
        qWarning("Someone has taken the seat");
        return false;
    }
    m_player = player;
    PlayerShow *playerShow = new PlayerShow(player);
    playerShow->setParentItem(this);
    emit playerEnter(player);
    return true;
}

void RoomSeat::createRobot()
{
    Player *robot = new Player("Robot" + QString::number(10));
    seated(robot);
}

QRectF RoomSeat::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void RoomSeat::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

void RoomSeat::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit enterHover();
}

void RoomSeat::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit leaveHover();
}

RoomSeatArea::RoomSeatArea(int numOfSeats)
    : m_width(g_Config.value("SizeOfView").toSizeF().width() - 200), m_height(g_Config.value("SizeOfView").toSizeF().height() - 200)
{
    for (int i = 0; i != numOfSeats; ++i) {
        addSeat();
    }
}

QRectF RoomSeatArea::boundingRect() const
{
    return QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
}

void RoomSeatArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

void RoomSeatArea::addSeat()
{
    RoomSeat *seat = new RoomSeat;
    seat->setParentItem(this);
    Seats.append(seat);
    connect(seat, SIGNAL(playerEnter(Player *)), this, SLOT(playerSeated(Player *)));
    adjustItems();
}

bool RoomSeatArea::addPlayer(Player *player)
{
    for (int i = 0; i != Seats.count(); ++i) {
        if (Seats.at(i)->isEmpty()) {
            Seats.at(i)->seated(player);
            return true;
        }
    }
    qWarning("No empty seat !");
    return false;
}

void RoomSeatArea::playerSeated(Player *player)
{
    Players.append(player);
}

void RoomSeatArea::adjustItems()
{
    int numOfSeats = Seats.count();
    for (int i = 0; i != numOfSeats; ++i) {
        Seats.at(i)->setPos(seatPos(i, numOfSeats));
    }
}

QPointF RoomSeatArea::seatPos(int i, int n)
{
    QRectF rect = boundingRect();
    QSizeF size = g_Config.value("SizeOfPhoto").toSizeF();
    if (n < 4) {
        qreal space = calSpace(rect.width(), size.width(), n);
        return QPointF(rect.left() + (i + 1) * (space + size.width()) - size.width() / 2,
                       rect.top() / 2 + rect.bottom() / 2);
    } else {
        qreal xSpace1 = calSpace(rect.width(), size.width(), n / 2);
        qreal xSpace2 = calSpace(rect.width(), size.width(), (n + 1) / 2);
        qreal ySpace = calSpace(rect.height(), size.height(), 2);
        if (i < n / 2) {
            return QPointF(rect.left() + (i + 1) * (xSpace1 + size.width()) - size.width() / 2,
                           rect.top() + ySpace + size.height() / 2);
        } else {
            return QPointF(rect.left() + (i - n / 2 + 1) * (xSpace2 + size.width()) - size.width() / 2,
                           rect.top() + 2 * (ySpace + size.height()) - size.height() / 2);
        }
    }
}

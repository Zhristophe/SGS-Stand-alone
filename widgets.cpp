#include "widgets.h"
#include "settings.h"
#include "button.h"
#include "seat.h"
#include <QPainter>
#include "graphicsscene.h"
#include <QPainter>
#include "operationpanel.h"

StartWidget::StartWidget(GraphicsScene *parent)
    : m_width(g_Config.value("SizeOfView").toSizeF().width()), m_height(g_Config.value("SizeOfView").toSizeF().height()),
      parentScene(parent)
{
    parentScene->addItem(this);

    btnEnterRoom = new Button("Enter room");
    btnEnterRoom->setParentItem(this);
    connect(btnEnterRoom, SIGNAL(clicked()), this, SLOT(enterRoom()));
}

void StartWidget::enterRoom()
{
    if (parentScene == nullptr) {
        qWarning("No parent scene");
        return;
    }
    RoomWidget *room = new RoomWidget(parentScene);
    parentScene->addItem(room);
    parentScene->currentWidget = room;
    parentScene->removeItem(this);
    delete this;
}

void StartWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

RoomWidget::RoomWidget(GraphicsScene *parent)
    : m_width(g_Config.value("SizeOfView").toSizeF().width()), m_height(g_Config.value("SizeOfView").toSizeF().height()),
      parentScene(parent)
{
    btnStartGame = new Button("Start game");
    btnStartGame->setPos(300 ,200);
    btnStartGame->setParentItem(this);
    connect(btnStartGame, SIGNAL(clicked()), this, SLOT(startGame()));

    area = new RoomSeatArea();
    area->setPos(-100, -100);
    area->setParentItem(this);
}

void RoomWidget::startGame()
{
    if (parentScene == nullptr) {
        qWarning("No parent scene");
        return;
    }
    GameWidget *game = new GameWidget(parentScene);
    parentScene->addItem(game);
    parentScene->currentWidget = game;
    parentScene->removeItem(this);
    delete this;
}

void RoomWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

GameWidget::GameWidget(GraphicsScene *parent)
    : m_width(g_Config.value("SizeOfView").toSizeF().width()), m_height(g_Config.value("SizeOfView").toSizeF().height()),
      parentScene(parent)
{
    parentScene->addItem(this);

    panel = new OperationPanel;
    panel->setParentItem(this);
}


void GameWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

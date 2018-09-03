#include "graphicsscene.h"
#include "settings.h"
#include "button.h"
#include "operationpanel.h"
#include <QDebug>
#include <QGraphicsView>
#include <QSizeF>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QThread>
#include "engine.h"
#include "carditem.h"
#include "gameevent.h"
#include <QApplication>
#include "event.h"
#include "seat.h"
#include "player.h"
#include "widgets.h"

GraphicsScene::GraphicsScene()
    : m_sceneState(SceneState::StateNone)
{
    connect(this, SIGNAL(sceneStateChanged(SceneState)), SLOT(changeSceneState(SceneState)));

    initialise();

//    setSceneState(SceneState::StateStart);

    currentWidget = new StartWidget(this);
}

GraphicsScene::~GraphicsScene()
{
    delete engine;
    delete gameThread;
}

GraphicsScene::SceneState GraphicsScene::sceneState() const
{
    return m_sceneState;
}

void GraphicsScene::setSceneState(SceneState state)
{
    if(m_sceneState != state) {
        m_sceneState = state;
        emit sceneStateChanged(state);
    }
}

void GraphicsScene::changeSceneState(SceneState state)
{
    clear();
    switch (state) {
    case SceneState::StateStart:
        {
//            Button *buttonEnterRoom = new Button("Enter Room");
//            connect(buttonEnterRoom, SIGNAL(clicked()), this, SLOT(enterRoom()));
//            addItem(buttonEnterRoom);

            currentWidget = new StartWidget(this);
        }
        break;
    case SceneState::StateRoom:
        {
//            Button *buttonStartGame = new Button("Start Game");
//            buttonStartGame->setPos(300, 200);
//            connect(buttonStartGame, SIGNAL(clicked()), this, SLOT(startGame()));
//            addItem(buttonStartGame);

//            int numOfSeats = g_Config.value("maxNumOfPlayers").toInt();
//            m_area = new RoomSeatArea(numOfSeats);
//            m_area->setPos(-100, -100);
//            addItem(m_area);

//            addItem(new RoomWidget);

//            m_area->addPlayer(&g_Player);
        }
        break;
    case SceneState::StateGame:
        {
            m_panel = new OperationPanel;
            engine = new Engine;
            gameThread = new QThread;
            engine->moveToThread(gameThread);
            connect(m_panel, SIGNAL(sendEvent(GameEvent *)), engine, SLOT(reciveEvent(GameEvent *)));
            connect(engine, SIGNAL(sendEvent(GameEvent *)), m_panel, SLOT(reciveEvent(GameEvent *)));

            foreach (Player *p, m_area->getPlayers()) {
                m_panel->addPlayer(p);
            }
            addItem(m_panel);

            gameThread->start();
            qDebug() << QThread::currentThreadId();
            engine->startGame(this);
            Event *e = new Event;
            QCoreApplication::postEvent(engine, e);
        }
        break;
    default:
        break;
    }
}

void GraphicsScene::initialise()
{
    // Ui
    QSize size = g_Config.value("SizeOfView").toSize();
    setSceneRect(-size.width() / 2, -size.height() / 2, size.width(), size.height());

    Button *buttonEnterRoom = new Button("Enter Room");
    connect(buttonEnterRoom, SIGNAL(clicked()), this, SLOT(enterRoom()));
    ItemsStart << buttonEnterRoom;

    Button *buttonStartGame = new Button("Start Game");
    buttonStartGame->setPos(300, 200);
    connect(buttonStartGame, SIGNAL(clicked()), this, SLOT(startGame()));
    ItemsRoom << buttonStartGame;

    for (int i = 0; i != 8; ++i) {
        RoomSeats << new RoomSeat;
    }

    // Game engine

    // Room settings

}

void GraphicsScene::enterRoom()
{
    setSceneState(SceneState::StateRoom);
}

void GraphicsScene::setBackgroundImage(const QString &fileName)
{
//    qDebug() << QThread::currentThreadId();
//    addPixmap(QPixmap(fileName).scaled(g_Config.value("SizeOfView").toSize()));
    addPixmap(QPixmap(fileName));
}

void GraphicsScene::drawBackground(QPainter *, const QRectF &)
{

}

void GraphicsScene::startGame()
{
    setSceneState(SceneState::StateGame);
}

QPointF GraphicsScene::seatPos(int i, int n)
{
    // Support 2, 4 ,8, i from 0
    QRectF rect = g_Config.value("RectOfView").toRectF() - QMarginsF(0, 0, 200, 200);
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

qreal GraphicsScene::calSpace(qreal W, qreal w, int n)
{
    return (W - n * w) / (n + 1);
}

bool GraphicsScene::addPlayer(Player* player)
{
    if (Players.count() >= g_Config.value("maxNumOfPlayers").toInt()) {
        qWarning("No empty seat");
        return false;
    }
    bool flag = false;
    foreach (Player* each, Players) {
        if (each->getId() == player->getId()) {
            flag = true;
            break;
        }
    }
    if (flag) {
        qWarning("The palyer has been here");
        return false;
    }
    Players.append(player);
    //
    return true;
}

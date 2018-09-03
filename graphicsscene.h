#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QList>

class Engine;
class QThread;
class OperationPanel;
class QSetting;
class Player;
class RoomSeatArea;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(SceneState sceneState READ sceneState WRITE setSceneState NOTIFY sceneStateChanged)

public:
    enum SceneState {
        StateNone,
        StateStart,
        StateRoom,
        StateGame
    };
    Q_ENUM(SceneState)

    GraphicsScene();
    ~GraphicsScene();

    SceneState sceneState() const;
    void setSceneState(SceneState state);
    void setBackgroundImage(const QString &fileName);
    OperationPanel *getPanel() const { return m_panel; }

    bool addPlayer(Player *player);

    friend class StartWidget;
    friend class RoomWidget;
    friend class GameWidget;

protected:
    void drawBackground(QPainter *, const QRectF &);

private:
    void initialise();
    QPointF seatPos(int i, int n);
    qreal calSpace(qreal W, qreal w, int n);

    SceneState m_sceneState;

    QList<QGraphicsItem *> ItemsStart;
    QList<QGraphicsItem *> ItemsRoom;
    QList<QGraphicsItem *> ItemsGame;
    QList<QGraphicsItem *> RoomSeats;
    QList<Player *> Players;

    Engine *engine;
    QThread *gameThread;
    OperationPanel *m_panel;
    RoomSeatArea *m_area;
    QGraphicsObject *currentWidget;

private slots:
    void changeSceneState(SceneState state);
    void enterRoom();
    void gotoScene(bool f) { f = 0; setSceneState(SceneState::StateRoom); }
    void startGame();

signals:
    void sceneStateChanged(SceneState state);
    void print();
};

#endif // GRAPHICSSCENE_H

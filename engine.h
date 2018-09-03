#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QDebug>
#include <QThread>

class GameEvent;
class GraphicsScene;
class Player;
class Card;
class OperationPanel;

class Engine : public QObject
{
    Q_OBJECT

public:
    Engine();
    ~Engine();

    void startGame(GraphicsScene *scene = nullptr);

    bool event(QEvent *e);

public slots:
    void print() { qDebug() << "ok" << QThread::currentThreadId(); }

    void reciveEvent(GameEvent *event);

private:
    QList<Player *> Players;
    QList<Card *> Pile;
    OperationPanel *panel;

signals:
    void sendEvent(GameEvent *);
};

#endif // ENGINE_H

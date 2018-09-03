#ifndef WIDGETS_H
#define WIDGETS_H

#include <QGraphicsObject>

class Button;
class RoomSeatArea;
class GraphicsScene;
class OperationPanel;

class StartWidget : public QGraphicsObject
{
    Q_OBJECT

public:
    StartWidget(GraphicsScene *parent);
    QRectF boundingRect() const { return QRectF(-m_width / 2, -m_height / 2, m_width, m_height); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;
    GraphicsScene *parentScene;

    // Widgets
    Button *btnEnterRoom;

private slots:
    void enterRoom();
};

class RoomWidget : public QGraphicsObject
{
    Q_OBJECT

public:
    RoomWidget(GraphicsScene *parent);

    QRectF boundingRect() const { return QRectF(-m_width / 2, -m_height / 2, m_width, m_height); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;
    GraphicsScene *parentScene;

    // Widgets
    Button *btnStartGame;
    RoomSeatArea *area;

private slots:
    void startGame();
};

class GameWidget : public QGraphicsObject
{
    Q_OBJECT

public:
    GameWidget(GraphicsScene *parent);

    QRectF boundingRect() const { return QRectF(-m_width / 2, -m_height / 2, m_width, m_height); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    qreal m_width, m_height;
    GraphicsScene *parentScene;

    // Widgets
    OperationPanel *panel;

private slots:

};


#endif // WIDGETS_H

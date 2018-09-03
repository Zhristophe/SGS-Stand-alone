#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"
#include "startscene.h"
#include "roomscene.h"

#include <QMainWindow>
#include <QGraphicsView>

class GraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void gotoScene(QGraphicsScene *);
//    QList<QAction *> getActions();

public slots:
    void startGame();

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void moveEvent(QMoveEvent *);
    virtual void closeEvent(QCloseEvent *event);
//    virtual void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsView *view;
    GraphicsScene *scene;
//    StartScene *startScene;
//    RoomScene *roomScene;

    QList<QAction *> actions;

    void restoreFromConfig();
};

#endif // MAINWINDOW_H

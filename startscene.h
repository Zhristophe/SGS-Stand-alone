#ifndef STARTSCENE_H
#define STARTSCENE_H

//#include "mainwindow.h"

#include <QGraphicsScene>
#include <QPushButton>

class MainWindow;

class StartScene : public QGraphicsScene
{
    Q_OBJECT

public:
    StartScene(MainWindow *window = nullptr);

    void addButton(QAction *action);

private:
    MainWindow *mainWindow;
    QPushButton *start_game;
};

#endif // STARTSCENE_H

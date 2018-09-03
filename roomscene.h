#ifndef ROOMSCENE_H
#define ROOMSCENE_H

#include "mainwindow.h"

#include <QGraphicsScene>
#include <QAction>

class RoomScene : public QGraphicsScene
{
    Q_OBJECT

public:
    RoomScene(MainWindow *window = nullptr);

    void addButton(QAction *action);

public slots:
    void returnStart();

private:
    MainWindow *mainWindow;
};

#endif // ROOMSCENE_H

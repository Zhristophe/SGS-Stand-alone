#include "roomscene.h"
#include "startscene.h"

#include <QPushButton>

RoomScene::RoomScene(MainWindow *window)
    : mainWindow(window)
{
    addText("room");

    QAction *actionReturn = new QAction;
    connect(actionReturn, SIGNAL(triggered()), this, SLOT(returnStart()));
    addButton(actionReturn);
}

void RoomScene::addButton(QAction *action)
{
    QPushButton *button = new QPushButton("return");
    connect(button, SIGNAL(clicked()), action, SLOT(trigger()));
    addWidget(button);
}

void RoomScene::returnStart()
{
    StartScene *startScene = new StartScene(mainWindow);
    mainWindow->gotoScene(startScene);
}

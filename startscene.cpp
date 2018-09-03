#include "startscene.h"
#include "mainwindow.h"

#include <QDebug>
#include <QGraphicsView>
#include <QAction>

StartScene::StartScene(MainWindow *window)
    : mainWindow(window)
{
    setBackgroundBrush(Qt::green);

    addText("Hello, world!");

//    addButton(window->getActions().at(0));
}

void StartScene::addButton(QAction *action)
{
    QPushButton *button = new QPushButton("new button");
    connect(button, SIGNAL(clicked()), action, SLOT(trigger()));
    addWidget(button);
}

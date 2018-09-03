#include "mainwindow.h"
#include "startscene.h"
#include "roomscene.h"
#include "graphicsscene.h"
#include "settings.h"

#include <QGraphicsView>
#include <QCloseEvent>
#include <QMessageBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QRect>
#include <QAction>
#include <QSizeF>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSize size = g_Config.value("SizeOfView", QSize(1000, 618)).toSize();

    scene = new GraphicsScene();
    view = new QGraphicsView(scene, this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGeometry(0, 0, size.width(), size.height());

    setMinimumSize(view->size());

//    QAction *actionStartGame = new QAction;
//    connect(actionStartGame, SIGNAL(triggered()), this, SLOT(startGame()));

//    StartScene *start_scene = new StartScene;

//    actions << actionStartGame;
//        foreach (QAction *action, actions)
//        start_scene->addButton(action);

//    view = new QGraphicsView(scene, this);
//    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view->setGeometry(0, 0, 800, 450);
//    setMinimumSize(view->size());

    restoreFromConfig();

//    gotoScene(start_scene);
}

MainWindow::~MainWindow()
{
    view->deleteLater();
    if (scene) {
        scene->deleteLater();
    }
}

void MainWindow::restoreFromConfig()
{
    resize(g_Config.value("WindowSize", QSize(1000, 618)).toSize());
    move(g_Config.value("WindowPosition", QPoint(100, 100)).toPoint());
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    view->move((width() - view->width()) / 2, (height() - view->height()) / 2);
}

void MainWindow::moveEvent(QMoveEvent *)
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::Ok;

    if (g_Config.ShowMsgBoxWhenExit) {
        QMessageBox msgBox(QMessageBox::Question, tr("SASGS"), tr("Are you sure to exit?"), QMessageBox::Ok | QMessageBox::Cancel, this);
        QCheckBox dontShowAgainCheckBox(tr("Don't Show Again"), &msgBox);

        QGridLayout *msgBoxLayout = qobject_cast<QGridLayout *>(msgBox.layout());
        if (NULL != msgBoxLayout) {
            QMargins margins = msgBoxLayout->contentsMargins();
            margins.setBottom(5);
            msgBoxLayout->setContentsMargins(margins);
            msgBoxLayout->addWidget(&dontShowAgainCheckBox, 3, 0, 1, 2, Qt::AlignLeft);
        }

        result = msgBox.exec();

        if (dontShowAgainCheckBox.isChecked()) {
            g_Config.ShowMsgBoxWhenExit = false;
            g_Config.setValue("ShowMsgBoxWhenExit", g_Config.ShowMsgBoxWhenExit);
        }
    }

    if (QMessageBox::Cancel == result) {
        event->ignore();
    } else {
        event->accept();
    }

    g_Config.setValue("WindowSize", size());
    g_Config.setValue("WindowPosition", pos());
}

void MainWindow::gotoScene(QGraphicsScene *scene)
{
    if (this->scene)
        this->scene->deleteLater();
//    this->scene = scene;
    view->setScene(scene);
}

void MainWindow::startGame()
{
    RoomScene *room_scene = new RoomScene(this);
    gotoScene(room_scene);
}

//QList<QAction *> MainWindow::getActions()
//{
//    return actions;
//}

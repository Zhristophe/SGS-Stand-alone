#include "settings.h"
#include <QDebug>
#include <QVariant>

Settings g_Config;

Settings::Settings()
    : QSettings("StandAloneSgs.org", "StandAloneSgs")
{
    // Ui
    initValue("id", "zrz");
    initValue("SizeOfView", QSizeF(1000, 618));
    initValue("RectOfView", QRectF(-500, -309, 1000, 618));
    initValue("SizeOfPhoto", QSizeF(124, 200));

    // Room infomation
    initValue("maxNumOfPlayers", 8);
}

void Settings::init()
{
    TextEditColor = QColor(value("TextEditColor", "white").toString());

    ShowMsgBoxWhenExit = value("ShowMsgBoxWhenExit", true).toBool();
}

void Settings::initValue(const QString &key, const QVariant &value)
{
    if (!contains(key)) {
        setValue(key, value);
    }
}

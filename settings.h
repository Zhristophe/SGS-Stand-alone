#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QRect>
#include <QColor>

class Settings : public QSettings
{
    Q_OBJECT

public:
    explicit Settings();
    void init();

    const QRectF Rect;

    QColor TextEditColor;

    // Ui
    bool ShowMsgBoxWhenExit;

private:
    void initValue(const QString &key, const QVariant &value);
};

extern Settings g_Config;

#endif // SETTINGS_H

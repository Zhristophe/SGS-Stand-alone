#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(int seat READ getSeat WRITE setSeat)

public:
    Player(QString id = "NoName");

    QString getId() const { return id; }
    void setId(const QString &id) { this->id = id; }

    QString getName() const { return name; }
    void setName(const QString &name) { this->name = name; }

    int getSeat() const { return seat; }
    void setSeat(int seat) { this->seat = seat; }

private:
    QString id, name;
    int seat;
};

extern Player g_Player;

#endif // PLAYER_H

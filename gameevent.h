#ifndef GAMEEVENT_H
#define GAMEEVENT_H

class GameEvent
{
    enum ChoiceType {
        Card,
        Player,
        Option
    };

public:
    explicit GameEvent();

    // from engine
//    QList<int> Cards;
//    QList<int> Players;

    // from Ui
    ChoiceType type;

};

#endif // GAMEEVENT_H


#ifndef EVENT_H
#define EVENT_H

#include <QEvent>

extern const QEvent::Type MyType;

class Event : public QEvent
{
public:
    explicit Event();
};

#endif // EVENT_H

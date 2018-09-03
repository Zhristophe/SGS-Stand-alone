#include "event.h"
#include <QDebug>

const QEvent::Type MyType = static_cast<QEvent::Type const>(QEvent::registerEventType(20000));

Event::Event()
    : QEvent(MyType)
{
}

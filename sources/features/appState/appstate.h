#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>

class AppStateEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        Loading,
        Menu,
        Gameplay,
        Quit,
    };
    Q_ENUM(Enum)
};

typedef AppStateEnumWrapper::Enum AppState;

#endif // APPSTATE_H

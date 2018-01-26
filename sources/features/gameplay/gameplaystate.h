#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <QObject>

class GameplayStateEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        Playing,
        Won,
        Lose,
    };
    Q_ENUM(Enum)
};

typedef GameplayStateEnumWrapper::Enum GameplayState;

#endif // GAMEPLAYSTATE_H

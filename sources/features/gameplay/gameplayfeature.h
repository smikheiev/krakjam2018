#ifndef GAMEPLAYFEATURE_H
#define GAMEPLAYFEATURE_H

#include <QObject>
#include <QMap>

#include "../../macros.h"
#include "gameplaystate.h"
#include "../appState/appstate.h"

class GameplayFeature : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(GameplayState, currentGameplayState)

public:
    explicit GameplayFeature(QObject *parent = nullptr);
    ~GameplayFeature();

public:
    Q_INVOKABLE void tryChangeStateTo(const GameplayState newGameplayState);

public slots:
    void onAppStateChanged(const AppState appState);

private:
    void setupPossibleStateTransitions();
    bool canChangeStateFromTo(const GameplayState stateFrom, const GameplayState stateTo) const;

private:
    QMap<GameplayState, QVector<GameplayState>*> mPossibleStateTransitions;
};

#endif // GAMEPLAYFEATURE_H

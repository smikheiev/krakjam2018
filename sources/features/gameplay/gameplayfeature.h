#ifndef GAMEPLAYFEATURE_H
#define GAMEPLAYFEATURE_H

#include <QObject>
#include <QMap>

#include "../../macros.h"
#include "gameplaystate.h"
#include "../appState/appstate.h"
#include "../characters/characterslogic.h"
#include "map/mapmodel.h"
#include "range/rangeslistmodel.h"
#include "esbeklogic.h"
#include "transmissionlogic.h"
#include "objectives/objectiveslogic.h"

class GameplayFeature : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(GameplayState, currentGameplayState)
    AUTO_Q_PROPERTY(MapModel*, mapModel)
    AUTO_Q_PROPERTY(CharactersLogic*, charactersLogic)
    AUTO_Q_PROPERTY(RangesListModel*, ranges)
    AUTO_Q_PROPERTY(EsbekLogic*, esbekLogic)
    AUTO_Q_PROPERTY(TransmissionLogic*, transmissionLogic)
    AUTO_Q_PROPERTY(ObjectivesLogic*, objectiveLogic)

public:
    explicit GameplayFeature(QObject *parent = nullptr);
    ~GameplayFeature();

public:
    Q_INVOKABLE void tryChangeStateTo(const GameplayState newGameplayState);
    Q_INVOKABLE void newRoundStartNeeded();

public slots:
    void onAppStateChanged(const AppState appState);
    void setRandomRangeOnMap();

signals:
    void objectiveCompleted();

private:
    void setupInitialRanges();
    void setupPossibleStateTransitions();
    bool canChangeStateFromTo(const GameplayState stateFrom, const GameplayState stateTo) const;

private:
    QMap<GameplayState, QVector<GameplayState>*> mPossibleStateTransitions;
    RangeModel* mHQRange;
};

#endif // GAMEPLAYFEATURE_H

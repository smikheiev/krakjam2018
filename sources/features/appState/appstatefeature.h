#ifndef APPSTATEFEATURE_H
#define APPSTATEFEATURE_H

#include <QObject>
#include <QMap>

#include "../../macros.h"
#include "appstate.h"
#include "../gameplay/gameplaystate.h"

class AppStateFeature : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(AppState, currentAppState)

public:
    explicit AppStateFeature(QObject *parent = nullptr);
    ~AppStateFeature();

public:
    Q_INVOKABLE void tryChangeStateTo(const AppState newAppState);

public slots:
    void onGameplayStateChanged(const GameplayState gameplayState);

private:
    void setupPossibleStateTransitions();
    bool canChangeStateFromTo(const AppState stateFrom, const AppState stateTo) const;

private:
    QMap<AppState, QVector<AppState>*> mPossibleStateTransitions;
};

#endif // APPSTATEFEATURE_H

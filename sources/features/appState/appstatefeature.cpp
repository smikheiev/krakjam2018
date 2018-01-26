#include <QVector>
#include <QDebug>

#include "appstatefeature.h"

AppStateFeature::AppStateFeature(QObject *parent)
    : QObject(parent)
    , m_currentAppState(AppState::None)
{
    setupPossibleStateTransitions();
}

AppStateFeature::~AppStateFeature()
{
    for (const AppState key : mPossibleStateTransitions.keys())
    {
        delete mPossibleStateTransitions.value(key);
    }
}

void AppStateFeature::tryChangeStateTo(const AppState newAppState)
{
    if (canChangeStateFromTo(m_currentAppState, newAppState))
    {
        set_currentAppState(newAppState);
    }
    else
    {
        qDebug() << "Can not change state from" << m_currentAppState << "to" << newAppState;
    }
}

void AppStateFeature::onGameplayStateChanged(const GameplayState gameplayState)
{
    if (gameplayState == GameplayState::None)
    {
        tryChangeStateTo(AppState::Menu);
    }
}

void AppStateFeature::setupPossibleStateTransitions()
{
    mPossibleStateTransitions.insert(AppState::None, new QVector<AppState>{AppState::Loading});
    mPossibleStateTransitions.insert(AppState::Loading, new QVector<AppState>{AppState::Menu});
    mPossibleStateTransitions.insert(AppState::Menu, new QVector<AppState>{AppState::Gameplay, AppState::Quit});
    mPossibleStateTransitions.insert(AppState::Gameplay, new QVector<AppState>{AppState::Menu});
}

bool AppStateFeature::canChangeStateFromTo(const AppState stateFrom, const AppState stateTo) const
{
    if (stateTo == AppState::None)
    {
        return false;
    }

    const QVector<AppState>* possibleStates = mPossibleStateTransitions.value(stateFrom, nullptr);
    if (possibleStates != nullptr)
    {
        return possibleStates->contains(stateTo);
    }
    return false;
}

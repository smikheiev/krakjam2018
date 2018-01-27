#include "featuresroot.h"

FeaturesRoot::FeaturesRoot(QObject *parent)
    : QObject(parent)
{
    createFeatures();
    connectFeatures();
}

void FeaturesRoot::createFeatures()
{
    m_appState = new AppStateFeature(this);
    m_exitApp = new ExitAppFeature(this);
    m_gameplay = new GameplayFeature(this);
}

void FeaturesRoot::connectFeatures()
{
    connect(appState(), SIGNAL(currentAppStateChanged(AppState)), exitApp(), SLOT(onAppStateChanged(AppState)));
    connect(appState(), SIGNAL(currentAppStateChanged(AppState)), gameplay(), SLOT(onAppStateChanged(AppState)));

    connect(gameplay(), SIGNAL(currentGameplayStateChanged(GameplayState)), appState(), SLOT(onGameplayStateChanged(GameplayState)));

    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveAdded(ObjectiveModel*)), gameplay(), SLOT(onObjectiveAdded(ObjectiveModel*)));
    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveRemoved(ObjectiveModel*)), gameplay(), SLOT(onObjectiveRemoved(ObjectiveModel*)));
}

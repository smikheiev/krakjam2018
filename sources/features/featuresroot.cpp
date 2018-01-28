#include "featuresroot.h"
#include "koza.h"

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
    m_sounds = new SoundsFeature(this);

    Koza* koza = new Koza(this);
    Koza::theKoza = koza;
    connect(koza, SIGNAL(showKoza()), this, SLOT(onShowKoza()));
}

void FeaturesRoot::connectFeatures()
{
    connect(appState(), SIGNAL(currentAppStateChanged(AppState)), exitApp(), SLOT(onAppStateChanged(AppState)));
    connect(appState(), SIGNAL(currentAppStateChanged(AppState)), gameplay(), SLOT(onAppStateChanged(AppState)));

    connect(gameplay(), SIGNAL(currentGameplayStateChanged(GameplayState)), appState(), SLOT(onGameplayStateChanged(GameplayState)));

    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveAdded(ObjectiveModel*)), gameplay(), SLOT(onObjectiveAdded(ObjectiveModel*)));
    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveRemoved(ObjectiveModel*)), gameplay(), SLOT(onObjectiveRemoved(ObjectiveModel*)));

    connect(gameplay()->esbekLogic(), SIGNAL(esbekCatchAntenaBoy()), gameplay()->scoreLogic(), SLOT(onEsbekCatchAntenaBoy()));

    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveCompleted()), gameplay()->scoreLogic(), SLOT(onMissionCompleted()));
    connect(gameplay()->objectiveLogic(), SIGNAL(objectiveCompleted()), gameplay()->esbekLogic(), SLOT(onObjectiveCompleted()));

    connect(gameplay()->hqRange(), SIGNAL(isTransmittingChanged(bool)), sounds(), SLOT(onIsSignalTransmittingChanged(bool)));
    connect(gameplay()->esbekLogic(), SIGNAL(esbekCatchAntenaBoy()), sounds(), SLOT(onAntennaBoyCatched()));
}

void FeaturesRoot::onShowKoza()
{
    QTimer::singleShot(300, this, SLOT(playKozaSound()));

    emit showKoza();
}

void FeaturesRoot::playKozaSound()
{
    sounds()->playSound(SoundType::Koza, false);
}

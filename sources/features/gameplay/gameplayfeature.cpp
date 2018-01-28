#include <QVector>
#include <QDebug>

#include "gameplayfeature.h"

GameplayFeature::GameplayFeature(QObject *parent)
    : QObject(parent)
    , m_currentGameplayState(GameplayState::None)
    , m_mapModel(new MapModel(this))
    , m_charactersLogic(new CharactersLogic(mapModel(), this))
    , m_ranges(new RangesListModel(this))
    , m_esbekLogic(new EsbekLogic(mapModel(), charactersLogic(), this))
    , m_transmissionLogic(new TransmissionLogic(this))
    , m_objectiveLogic(new ObjectivesLogic(mapModel(), this))
    , m_scoreLogic(new ScoreLogic(this))
    , mHQRange(new RangeModel(this))
{
    setupPossibleStateTransitions();
    setupInitialRanges();

    transmissionLogic()->init(charactersLogic(), objectiveLogic()->objectives(), mHQRange);
    connect(objectiveLogic(), SIGNAL(objectiveCompleted()), this, SIGNAL(objectiveCompleted()));
}

GameplayFeature::~GameplayFeature()
{
    for (const GameplayState key : mPossibleStateTransitions.keys())
    {
        delete mPossibleStateTransitions.value(key);
    }
}

void GameplayFeature::tryChangeStateTo(const GameplayState newGameplayState)
{
    if (canChangeStateFromTo(m_currentGameplayState, newGameplayState))
    {
        set_currentGameplayState(newGameplayState);

        if (newGameplayState == GameplayState::Playing) { // haczorex?
            newRoundStartNeeded();
        }
    }
    else
    {
        qDebug() << "Can not change state from" << m_currentGameplayState << "to" << newGameplayState;
    }
}

void GameplayFeature::newRoundStartNeeded()
{
    charactersLogic()->restartPositionsAllAntenaBoys();
    esbekLogic()->resetEsbeks();
    objectiveLogic()->startNextObjectiveTimeout();
    transmissionLogic()->set_isRoundFailed(false);
    scoreLogic()->reset();
    emit restartTimerNeeded();
}

void GameplayFeature::restartRoundNeeded()
{
    charactersLogic()->restartPositionsAllAntenaBoys();
    esbekLogic()->resetEsbeks();
    transmissionLogic()->set_isRoundFailed(false);
    scoreLogic()->reset();
    emit restartTimerNeeded();
}

void GameplayFeature::roundFailed()
{
    transmissionLogic()->set_isRoundFailed(true);
}

void GameplayFeature::onAppStateChanged(const AppState appState)
{
    if (appState == AppState::Gameplay)
    {
        tryChangeStateTo(GameplayState::Playing);
    }
}

void GameplayFeature::onObjectiveAdded(ObjectiveModel *objective)
{
    ranges()->add(objective->range());
}

void GameplayFeature::onObjectiveRemoved(ObjectiveModel *objective)
{
    ranges()->remove(objective->range());
}

void GameplayFeature::setupInitialRanges()
{
    for (int i = 0; i < charactersLogic()->antenaBoyList().count(); ++i)
    {
        QVariant antenaBoyModelQVariant = charactersLogic()->antenaBoyList().at(i);
        AntenaBoyModel* antenaBoyModel = antenaBoyModelQVariant.value<AntenaBoyModel*>();
        ranges()->add(antenaBoyModel->range());
    }

    QPoint hqPos = mapModel()->getHQPosition();
    mHQRange->set_posX(hqPos.x() * TILE_SIZE);
    mHQRange->set_posY(hqPos.y() * TILE_SIZE);
    mHQRange->set_radius(HQ_RANGE_RADIUS);

    ranges()->add(mHQRange);
}

void GameplayFeature::setupPossibleStateTransitions()
{
    mPossibleStateTransitions.insert(GameplayState::None, new QVector<GameplayState>{GameplayState::Playing});
    mPossibleStateTransitions.insert(GameplayState::Playing, new QVector<GameplayState>{GameplayState::Won, GameplayState::Lose});
    mPossibleStateTransitions.insert(GameplayState::Won, new QVector<GameplayState>{GameplayState::None});
    mPossibleStateTransitions.insert(GameplayState::Lose, new QVector<GameplayState>{GameplayState::None});
}

bool GameplayFeature::canChangeStateFromTo(const GameplayState stateFrom, const GameplayState stateTo) const
{
    const QVector<GameplayState>* possibleStates = mPossibleStateTransitions.value(stateFrom, nullptr);
    if (possibleStates != nullptr)
    {
        return possibleStates->contains(stateTo);
    }
    return false;
}

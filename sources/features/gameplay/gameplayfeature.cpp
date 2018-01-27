#include <QVector>
#include <QDebug>

#include "gameplayfeature.h"

GameplayFeature::GameplayFeature(QObject *parent)
    : QObject(parent)
    , m_currentGameplayState(GameplayState::None)
    , m_charactersLogic(new CharactersLogic(this))
    , m_mapModel(new MapModel(this))
    , m_ranges(new RangesListModel(this))
    , m_esbekLogic(new EsbekLogic(m_mapModel, this))
{
    setupPossibleStateTransitions();

    charactersLogic()->setMapModel(mapModel());

    TEST_mSetRandomRangeOnMapTimer.setInterval(1500);
    TEST_mSetRandomRangeOnMapTimer.setSingleShot(false);
    connect(&TEST_mSetRandomRangeOnMapTimer, SIGNAL(timeout()), this, SLOT(setRandomRangeOnMap()));
    TEST_mSetRandomRangeOnMapTimer.start();
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
    }
    else
    {
        qDebug() << "Can not change state from" << m_currentGameplayState << "to" << newGameplayState;
    }
}

void GameplayFeature::onAppStateChanged(const AppState appState)
{
    if (appState == AppState::Gameplay)
    {
        tryChangeStateTo(GameplayState::Playing);
    }
}

void GameplayFeature::setRandomRangeOnMap()
{
    if (m_ranges->rowCount() >= 5)
    {
        m_ranges->removeAt(0);
    }

    int randomColumn = (qrand() % mapModel()->width());
    int randomRow = (qrand() % mapModel()->height());
    qreal randomRadius = ((qrand() % 25 + 5) / (qreal)10);

    RangeModel* rangeModel = new RangeModel(this);
    rangeModel->setToColumn(randomColumn);
    rangeModel->setToRow(randomRow);
    rangeModel->set_radius(randomRadius);

    m_ranges->add(rangeModel);
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

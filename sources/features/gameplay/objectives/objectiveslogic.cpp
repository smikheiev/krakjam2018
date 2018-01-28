#include "objectiveslogic.h"
#include "../constants.h"
#include <QDebug>

ObjectivesLogic::ObjectivesLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_objectives(new ObjectivesListModel(this))
    , mMapModel(mapModel)
{
}

void ObjectivesLogic::setNextRandomObjective(int excludePosX, int excludePosY)
{
    QVector<TileModel*> objectiveTiles;
    for (int i = 0; i < mMapModel->count(); i++)
    {
        TileModel* tile = mMapModel->getTileByIndex(i);
        if (tile->tileType() == TileType::House_PossibleTarget)
        {
            bool samePosX = tile->posX() - TILE_SIZE / 2 == excludePosX;
            bool samePosY = tile->posY() - TILE_SIZE / 2 == excludePosY;

            if (samePosX && samePosY) continue;
            objectiveTiles.append(tile);
        }
    }

    int randomTileIndex = qrand() % objectiveTiles.length();
    TileModel* objectiveTile = objectiveTiles.at(randomTileIndex);

    ObjectiveModel* objective = new ObjectiveModel(this);
    objective->set_posX(objectiveTile->posX() - TILE_SIZE / 2);
    objective->set_posY(objectiveTile->posY() - TILE_SIZE / 2);
    objectives()->add(objective);

    emit objectiveAdded(objective);
    connectObjective(objective);
}

void ObjectivesLogic::clearObjective(ObjectiveModel *objective)
{
    emit objectiveRemoved(objective);
    disconnectObjective(objective);
    objectives()->remove(objective);
}

void ObjectivesLogic::startNextObjectiveTimeout()
{
    setNextRandomObjective(mLastDoneObjectivePosX, mLastDoneObjectivePosY);
}

void ObjectivesLogic::connectObjective(ObjectiveModel *objective)
{
    connect(objective, SIGNAL(isDoneChanged(bool)), this, SLOT(onObjectiveIsDone()));
}

void ObjectivesLogic::disconnectObjective(ObjectiveModel *objective)
{
    disconnect(objective, SIGNAL(isDoneChanged(bool)), this, SLOT(onObjectiveIsDone()));
}

void ObjectivesLogic::onObjectiveIsDone()
{
    ObjectiveModel* doneObjective = nullptr;
    for (int i = 0; i < objectives()->rowCount(); ++i)
    {
        ObjectiveModel* objective = objectives()->at(i);
        if (objective->isDone())
        {
            doneObjective = objective;
            break;
        }
    }

    if (doneObjective != nullptr)
    {
        mLastDoneObjectivePosX = doneObjective->posX();
        mLastDoneObjectivePosY = doneObjective->posY();

        clearObjective(doneObjective);
    }
    else
    {
        mLastDoneObjectivePosX = -1;
        mLastDoneObjectivePosY = -1;
    }

    emit objectiveCompleted();

    startNextObjectiveTimeout();
}

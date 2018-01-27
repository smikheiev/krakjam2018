#include "objectiveslogic.h"

ObjectivesLogic::ObjectivesLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_objectives(new ObjectivesListModel(this))
    , mMapModel(mapModel)
{
    mSetNextObjectiveTimer.setInterval(1000);
    mSetNextObjectiveTimer.setSingleShot(true);

    connect(&mSetNextObjectiveTimer, SIGNAL(timeout()), this, SLOT(onSetNextObjectiveTimeout()));
    mSetNextObjectiveTimer.start();
}

void ObjectivesLogic::setNextRandomObjective(int excludePosX, int excludePosY)
{
    QVector<TileModel*> objectiveTiles;
    for (int i = 0; i < mMapModel->count(); i++)
    {
        TileModel* tile = mMapModel->getTileByIndex(i);
        if (tile->posX() == excludePosX && tile->posY() == excludePosY) continue;
        if (tile->tileType() == TileType::Target) objectiveTiles.append(tile);
    }

    if (objectiveTiles.length() == 0)
    {
        mLastDoneObjectivePosX = -1;
        mLastDoneObjectivePosY = -1;
        mSetNextObjectiveTimer.start();
        return;
    }

    int randomTileIndex = qrand() % objectiveTiles.length();
    TileModel* objectiveTile = objectiveTiles.at(randomTileIndex);

    ObjectiveModel* objective = new ObjectiveModel(this);
    objective->set_posX(objectiveTile->posX());
    objective->set_posY(objectiveTile->posY());
    objectives()->add(objective);

    connectObjective(objective);
}

void ObjectivesLogic::clearObjective(ObjectiveModel *objective)
{
    disconnectObjective(objective);
    objectives()->remove(objective);
}

void ObjectivesLogic::connectObjective(ObjectiveModel *objective)
{
    connect(objective, SIGNAL(isDoneChanged(bool)), this, SLOT(onObjectiveIsDone()));
}

void ObjectivesLogic::disconnectObjective(ObjectiveModel *objective)
{
    disconnect(objective, SIGNAL(isDoneChanged(bool)), this, SLOT(onObjectiveIsDone()));
}

void ObjectivesLogic::onSetNextObjectiveTimeout()
{
    setNextRandomObjective(mLastDoneObjectivePosX, mLastDoneObjectivePosY);
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

    mSetNextObjectiveTimer.start();
}

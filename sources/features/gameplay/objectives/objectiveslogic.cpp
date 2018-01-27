#include "objectiveslogic.h"

ObjectivesLogic::ObjectivesLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , mMapModel(mapModel)
{
    addObjective();
}

void ObjectivesLogic::addObjective()
{
    for (int i = 0; i < mMapModel->count(); i++) {
        TileModel* tile = mMapModel->getTileByIndex(i);

        if (tile->tileType() == TileType::Target) {
            ObjectiveModel* objectiveModel = new ObjectiveModel(this);
            objectiveModel->set_posX(tile->posX());
            objectiveModel->set_posY(tile->posY());

            mObjectivesList.append(objectiveModel);
        }
    }
}

QList<ObjectiveModel*> *ObjectivesLogic::objectivesList()
{
    return &mObjectivesList;
}

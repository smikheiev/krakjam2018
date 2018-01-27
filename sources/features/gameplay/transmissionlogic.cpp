#include <QtMath>

#include "transmissionlogic.h"

TransmissionLogic::TransmissionLogic(QObject* parent)
    : QObject(parent)
{
}

void TransmissionLogic::setHQRange(RangeModel *rangeModel)
{
    mHQRangeModel = rangeModel;
}

void TransmissionLogic::init(CharactersLogic *charactersLogic, MapModel *mapModel)
{
    for (AntenaBoyModel* antenaBoy : charactersLogic->mAntenaBoyModel) {
        mAntenaBoyList.append(antenaBoy);
    }

    for (int i=0; i<mapModel->count(); i++) {
        TileModel* tile = mapModel->getTileByIndex(i);

        if (tile->tileType() == TileType::Headquarter) {
            RangeModel* hqRangeModel = new RangeModel(this);
            hqRangeModel->set_posX(tile->posX());
            hqRangeModel->set_posY(tile->posY());
            hqRangeModel->set_radius(15);
            setHQRange(hqRangeModel);
        }

        if (tile->tileType() == TileType::Target) {
            ObjectiveModel* target = new ObjectiveModel(this);
            target->set_posX(tile->posX());
            target->set_posY(tile->posY());
            addObejctiveModel(target);
        }
    }
}

void TransmissionLogic::addAntenaBoyModel(AntenaBoyModel *antenaBoyModel)
{
    mAntenaBoyList.append(antenaBoyModel);
}

void TransmissionLogic::addObejctiveModel(ObjectiveModel *objectiveModel)
{
    mObjectiveList.append(objectiveModel);
}

qreal TransmissionLogic::distance(int posX_1, int posY_1, int posX_2, int posY_2) {
    return qSqrt(qPow(posX_2 - posX_1, 2) + qPow(posY_2 - posY_1, 2));
}

void TransmissionLogic::checkTransmission()
{
    bool isAnyTransmissionReached = false;

    QList<AntenaBoyModel*> alreadyTouchedBoys;
    QList<AntenaBoyModel*> transmittingBoys;
    QList<ObjectiveModel*> transmittingObjectives;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        int range = antenaBoy->range()->radius() + mHQRangeModel->radius();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), mHQRangeModel->posX(), mHQRangeModel->posY());
        if (range > distanceValue) {
            alreadyTouchedBoys.append(antenaBoy);
            if (isTransmissionReached(antenaBoy, &alreadyTouchedBoys, &transmittingBoys, &transmittingObjectives)) {
                if (!transmittingBoys.contains(antenaBoy))
                {
                    transmittingBoys.append(antenaBoy);
                }
                isAnyTransmissionReached = true;
            }
        }
    }

    mHQRangeModel->set_isTransmitting(isAnyTransmissionReached);
    for (ObjectiveModel* objectiveModel : mObjectiveList)
    {
        bool isTransmitting = transmittingObjectives.contains(objectiveModel);
        objectiveModel->range()->set_isTransmitting(isTransmitting);
    }
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList)
    {
        bool isTransmitting = transmittingBoys.contains(antenaBoy);
        antenaBoy->range()->set_isTransmitting(isTransmitting);
    }
}

bool TransmissionLogic::isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<AntenaBoyModel*>* alreadyCheckedBoys, QList<AntenaBoyModel*>* transmittingBoys, QList<ObjectiveModel*>* transmittingObjectives)
{
    bool result = false;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (alreadyCheckedBoys->contains(antenaBoy)) continue;

        int range = rootAntenaBoy->range()->radius() + antenaBoy->range()->radius();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            alreadyCheckedBoys->append(antenaBoy);
            if (isTransmissionReached(antenaBoy, alreadyCheckedBoys, transmittingBoys, transmittingObjectives)) {
                antenaBoy->range()->set_isTransmitting(true);
                if (!transmittingBoys->contains(antenaBoy))
                {
                    transmittingBoys->append(antenaBoy);
                }
                result = true;
            }
        }
    }

    for (ObjectiveModel* objectiveModel : mObjectiveList) {
        int range = rootAntenaBoy->range()->radius() + objectiveModel->range()->radius();
        qreal distanceValue = distance(objectiveModel->posX(), objectiveModel->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            transmittingObjectives->append(objectiveModel);
            return true;
        }
    }

    return result;
}

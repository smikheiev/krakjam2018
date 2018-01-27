#include <QtMath>

#include "transmissionlogic.h"

TransmissionLogic::TransmissionLogic(QObject* parent)
    : QObject(parent)
{
}

void TransmissionLogic::setHQModel(HQModel *hqModel)
{
    mHqModel = hqModel;
}

void TransmissionLogic::init(CharactersLogic *charactersLogic, MapModel *mapModel)
{
    for (AntenaBoyModel* antenaBoy : charactersLogic->mAntenaBoyModel) {
        mAntenaBoyList.append(antenaBoy);
    }

    for (int i=0; i<mapModel->count(); i++) {
        TileModel* tile = mapModel->getTileByIndex(i);

        if (tile->tileType() == TileType::Headquarter) {
            HQModel* headquarter = new HQModel(this);
            headquarter->set_posX(tile->posX());
            headquarter->set_posY(tile->posY());
            setHQModel(headquarter);
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
    mHqModel->set_isTransitionOnLine(false);
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        antenaBoy->set_transmissionOnLine(false);
    }

    QList<AntenaBoyModel*> alreadyTouchedBoys;
    QList<ObjectiveModel*> transmittingObjectives;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        int range = antenaBoy->range()->radius() + mHqModel->range();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), mHqModel->posX(), mHqModel->posY());
        if (range > distanceValue) {
            alreadyTouchedBoys.append(antenaBoy);
            if (isTransmissionReached(antenaBoy, &alreadyTouchedBoys, &transmittingObjectives)) {
                antenaBoy->set_transmissionOnLine(true);
                mHqModel->set_isTransitionOnLine(true);
            }
        }
    }
    for (ObjectiveModel* objectiveModel : mObjectiveList)
    {
        bool isTransmitting = transmittingObjectives.contains(objectiveModel);
        objectiveModel->set_isTransmissionOnLine(isTransmitting);
    }
}

bool TransmissionLogic::isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<AntenaBoyModel*>* alreadyTouchedBoys, QList<ObjectiveModel*>* transmittingObjectives)
{
    bool result = false;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (alreadyTouchedBoys->contains(antenaBoy)) continue;

        int range = rootAntenaBoy->range()->radius() + antenaBoy->range()->radius();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            alreadyTouchedBoys->append(antenaBoy);
            if (isTransmissionReached(antenaBoy, alreadyTouchedBoys, transmittingObjectives)) {
                antenaBoy->set_transmissionOnLine(true);
                result = true;
            }
        }
    }

    for (ObjectiveModel* objectiveModel : mObjectiveList) {
        int range = rootAntenaBoy->range()->radius() + objectiveModel->range();
        qreal distanceValue = distance(objectiveModel->posX(), objectiveModel->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            transmittingObjectives->append(objectiveModel);
            return true;
        }
    }

    return result;
}

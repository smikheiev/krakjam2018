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

#include <QtMath>
#include <QDebug>
qreal TransmissionLogic::distance(int posX_1, int posY_1, int posX_2, int posY_2) {
    return qSqrt(qPow(posX_2 - posX_1, 2) + qPow(posY_2 - posY_1, 2));
}

void TransmissionLogic::checkTransmission()
{
    mHqModel->set_isTransitionOnLine(false);
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        antenaBoy->set_transmissionOnLine(false);
    }

    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        int range = antenaBoy->range()->radius() + mHqModel->range();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), mHqModel->posX(), mHqModel->posY());
        if (range > distanceValue) {
            QList<int> touchedIdList;
            touchedIdList.append(antenaBoy->id());
            if (isTransmissionReached(antenaBoy, &touchedIdList)) {
                antenaBoy->set_transmissionOnLine(true);
                mHqModel->set_isTransitionOnLine(true);
            }
        }
    }
}

#include <QDebug>
bool TransmissionLogic::isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<int>* alreadyTouchedBoys)
{
    bool result = false;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (alreadyTouchedBoys->contains(antenaBoy->id())) continue;

        int range = rootAntenaBoy->range()->radius() + antenaBoy->range()->radius();
        qreal distanceValue = distance(antenaBoy->posX(), antenaBoy->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            alreadyTouchedBoys->append(antenaBoy->id());
            if (isTransmissionReached(antenaBoy, alreadyTouchedBoys)) {
                antenaBoy->set_transmissionOnLine(true);
                result = true;
            }
        }
    }

    for (ObjectiveModel* objectiveModel : mObjectiveList) {
        objectiveModel->set_isTransmissionOnLine(false);
        int range = rootAntenaBoy->range()->radius() + objectiveModel->range();
        qreal distanceValue = distance(objectiveModel->posX(), objectiveModel->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            objectiveModel->set_isTransmissionOnLine(true);
            qDebug() << "SUKCES";
            return true;
        }
    }

    return result;
}

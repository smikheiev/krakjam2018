#include <QtMath>

#include "transmissionlogic.h"
#include "../../utils.h"

TransmissionLogic::TransmissionLogic(QObject* parent)
    : QObject(parent)
    , m_isRoundFailed(false)
    , mHQRangeModel(nullptr)
    , mObjectivesList(nullptr)
{
}

void TransmissionLogic::init(CharactersLogic *charactersLogic, ObjectivesListModel *objectivesList, RangeModel *hqRange)
{
    mObjectivesList = objectivesList;
    mHQRangeModel = hqRange;

    for (AntenaBoyModel* antenaBoy : charactersLogic->mAntenaBoyList) {
        mAntenaBoyList.append(antenaBoy);
    }
}

void TransmissionLogic::checkTransmission()
{
    bool isAnyTransmissionReached = false;

    QList<AntenaBoyModel*> alreadyTouchedBoys;
    QList<AntenaBoyModel*> transmittingBoys;
    QList<ObjectiveModel*> transmittingObjectives;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        int range = antenaBoy->range()->radius() + mHQRangeModel->radius();
        qreal distanceValue = Utils::distance(antenaBoy->posX(), antenaBoy->posY(), mHQRangeModel->posX(), mHQRangeModel->posY());
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
    for (int i = 0; i < mObjectivesList->rowCount(); ++i)
    {
        ObjectiveModel* objectiveModel = mObjectivesList->at(i);
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
    if (isRoundFailed()) {
        return true;
    }

    bool result = false;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (alreadyCheckedBoys->contains(antenaBoy)) continue;

        int range = rootAntenaBoy->range()->radius() + antenaBoy->range()->radius();
        qreal distanceValue = Utils::distance(antenaBoy->posX(), antenaBoy->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
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

    for (int i = 0; i < mObjectivesList->rowCount(); ++i)
    {
        ObjectiveModel* objectiveModel = mObjectivesList->at(i);
        int range = rootAntenaBoy->range()->radius() + objectiveModel->range()->radius();
        qreal distanceValue = Utils::distance(objectiveModel->posX(), objectiveModel->posY(), rootAntenaBoy->posX(), rootAntenaBoy->posY());
        if (range > distanceValue) {
            transmittingObjectives->append(objectiveModel);
            return true;
        }
    }

    return result;
}

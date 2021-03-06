#ifndef TRANSMISSIONLOGIC_H
#define TRANSMISSIONLOGIC_H

#include <QObject>
#include <QList>

#include "../characters/antenaboymodel.h"
#include "map/mapmodel.h"
#include "../characters/characterslogic.h"
#include "../../macros.h"
#include "objectives/objectiveslistmodel.h"

class TransmissionLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(bool, isRoundFailed)

public:
    TransmissionLogic(QObject* parent);

    void init(CharactersLogic* charactersLogic, ObjectivesListModel* objectivesList, RangeModel* hqRange);
    Q_INVOKABLE void checkTransmission();

private:
    RangeModel* mHQRangeModel;
    QList<AntenaBoyModel*> mAntenaBoyList;
    ObjectivesListModel* mObjectivesList;

    bool isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<AntenaBoyModel*>* alreadyCheckedBoys, QList<AntenaBoyModel*>* transmittingBoys, QList<ObjectiveModel*>* transmittingObjectives);
};

#endif // TRANSMISSIONLOGIC_H

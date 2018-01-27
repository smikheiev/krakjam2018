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

public:
    TransmissionLogic(QObject* parent);

    void setHQRange(RangeModel* rangeModel);

    void init(CharactersLogic* charactersLogic, MapModel* mapModel, ObjectivesListModel* objectivesList);
    Q_INVOKABLE void checkTransmission();

private:
    RangeModel* mHQRangeModel;
    QList<AntenaBoyModel*> mAntenaBoyList;
    ObjectivesListModel* mObjectivesList;

    qreal distance(int posX_1, int posY_1, int posX_2, int posY_2);
    bool isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<AntenaBoyModel*>* alreadyCheckedBoys, QList<AntenaBoyModel*>* transmittingBoys, QList<ObjectiveModel*>* transmittingObjectives);
};

#endif // TRANSMISSIONLOGIC_H

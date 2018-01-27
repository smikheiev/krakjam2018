#ifndef TRANSMISSIONLOGIC_H
#define TRANSMISSIONLOGIC_H

#include <QObject>
#include <QList>

#include "../characters/antenaboymodel.h"
#include "map/hqmodel.h"
#include "map/objectivemodel.h"
#include "map/mapmodel.h"
#include "../characters/characterslogic.h"
#include "../../macros.h"

class TransmissionLogic : public QObject
{
    Q_OBJECT

public:
    TransmissionLogic(QObject* parent);

    void setHQModel(HQModel* hqModel_);

    void init(CharactersLogic* charactersLogic, MapModel* mapModel);
    Q_INVOKABLE void checkTransmission();

private:
    HQModel* mHqModel;
    QList<AntenaBoyModel*> mAntenaBoyList;
    QList<ObjectiveModel*> mObjectiveList;

    qreal distance(int posX_1, int posY_1, int posX_2, int posY_2);
    bool isTransmissionReached(AntenaBoyModel* rootAntenaBoy, QList<int>* alreadyTouchedBoys);
    void addAntenaBoyModel(AntenaBoyModel* antenaBoyModel);
    void addObejctiveModel(ObjectiveModel* objectiveModel);
};

#endif // TRANSMISSIONLOGIC_H

#ifndef OBJECTIVESLOGIC_H
#define OBJECTIVESLOGIC_H

#include <QObject>

#include "../map/mapmodel.h"
#include "../map/objectivemodel.h"

class ObjectivesLogic : public QObject
{
    Q_OBJECT

public:
    explicit ObjectivesLogic(MapModel* mapModel, QObject *parent = nullptr);

    void addObjective();
    void clearObjective();

    QList<ObjectiveModel*>* objectivesList();

private:
    MapModel* mMapModel;
    QList<ObjectiveModel*> mObjectivesList;
};

#endif // OBJECTIVESLOGIC_H

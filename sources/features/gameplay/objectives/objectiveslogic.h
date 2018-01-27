#ifndef OBJECTIVESLOGIC_H
#define OBJECTIVESLOGIC_H

#include <QObject>
#include <QTimer>

#include "../map/mapmodel.h"
#include "../map/objectivemodel.h"

class ObjectivesLogic : public QObject
{
    Q_OBJECT

public:
    explicit ObjectivesLogic(MapModel* mapModel, QObject *parent = nullptr);

    void setNextRandomObjective(int excludePosX, int excludePosY);
    void clearObjective(ObjectiveModel* objective);

    QList<ObjectiveModel*>* objectivesList();

private:
    void connectObjective(ObjectiveModel* objective);
    void disconnectObjective(ObjectiveModel* objective);

private slots:
    void onSetNextObjectiveTimeout();
    void onObjectiveIsDone();

private:
    MapModel* mMapModel;
    QList<ObjectiveModel*> mObjectivesList;
    QTimer mSetNextObjectiveTimer;

    int mLastDoneObjectivePosX = -1;
    int mLastDoneObjectivePosY = -1;
};

#endif // OBJECTIVESLOGIC_H

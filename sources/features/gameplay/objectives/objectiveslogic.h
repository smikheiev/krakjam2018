#ifndef OBJECTIVESLOGIC_H
#define OBJECTIVESLOGIC_H

#include <QObject>
#include <QTimer>

#include "../../../macros.h"
#include "../map/mapmodel.h"
#include "objectiveslistmodel.h"

class ObjectivesLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(ObjectivesListModel*, objectives)

public:
    explicit ObjectivesLogic(MapModel* mapModel, QObject *parent = nullptr);

    void clearObjective(ObjectiveModel* objective);
    void startNextObjectiveTimeout();
    void reset();

public slots:
    void onEsbekCatchAntenaBoy();

private:
    void setNextRandomObjective(int excludePosX, int excludePosY, ObjectiveModel::OBJ_TYPE objectiveType);
    void connectObjective(ObjectiveModel* objective);
    void disconnectObjective(ObjectiveModel* objective);

signals:
    void objectiveCompleted();
    void jailOpend();

private slots:
    void onObjectiveIsDone();

private:
    MapModel* mMapModel;

    int mLastDoneObjectivePosX = -1;
    int mLastDoneObjectivePosY = -1;

signals:
    void objectiveAdded(ObjectiveModel* objective);
    void objectiveRemoved(ObjectiveModel* objective);
};

#endif // OBJECTIVESLOGIC_H

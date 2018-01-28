#ifndef OBJECTIVEMODEL_H
#define OBJECTIVEMODEL_H

#include <QObject>
#include <QTimer>

#include "../../../macros.h"
#include "../range/rangemodel.h"

class ObjectiveModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(RangeModel*, range)
    AUTO_Q_PROPERTY_CONSTANT(int, transmissionTime)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(bool, isDone)

public:
    ObjectiveModel(QObject* parent);

    enum OBJ_TYPE {
        ORDER = 0, JAIL
    };

    AUTO_Q_PROPERTY(OBJ_TYPE, type)

private slots:
    void onIsTransmittingChanged();
    void onTransmissionTimerTimeout();

private:
    void onTransmissionStarted();
    void onTransmissionAborted();
    void onTransmissionFinished();

private:
    QTimer mTransmissionTimer;
};

#endif // OBJECTIVEMODEL_H

#ifndef OBJECTIVEMODEL_H
#define OBJECTIVEMODEL_H

#include <QObject>
#include <QTimer>

#include "../../../macros.h"

class ObjectiveModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, range)
    AUTO_Q_PROPERTY_CONSTANT(int, transmissionTime)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(bool, isTransmissionOnLine)
    AUTO_Q_PROPERTY(bool, isDone)

public:
    ObjectiveModel(QObject* parent);

private slots:
    void onIsTransmissionOnlineChanged();
    void onTransmissionTimerTimeout();

private:
    void onTransmissionStarted();
    void onTransmissionAborted();
    void onTransmissionFinished();

private:
    QTimer mTransmissionTimer;
};

#endif // OBJECTIVEMODEL_H

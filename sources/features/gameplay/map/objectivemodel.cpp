#include <QDebug>

#include "objectivemodel.h"

ObjectiveModel::ObjectiveModel(QObject* parent):
    QObject(parent)
    , m_range(15)
    , m_transmissionTime(3000)
    , m_posX(0)
    , m_posY(0)
    , m_isTransmissionOnLine(false)
    , m_isDone(false)
{
    mTransmissionTimer.setInterval(transmissionTime());
    mTransmissionTimer.setSingleShot(true);
    mTransmissionTimer.stop();

    connect(&mTransmissionTimer, SIGNAL(timeout()), this, SLOT(onTransmissionTimerTimeout()));
    connect(this, SIGNAL(isTransmissionOnLineChanged(bool)), this, SLOT(onIsTransmissionOnlineChanged()));
}

void ObjectiveModel::onIsTransmissionOnlineChanged()
{
    if (isTransmissionOnLine())
    {
        onTransmissionStarted();
    }
    else
    {
        onTransmissionAborted();
    }
}

void ObjectiveModel::onTransmissionTimerTimeout()
{
    onTransmissionFinished();
}

void ObjectiveModel::onTransmissionStarted()
{
    qDebug() << "started";
    mTransmissionTimer.start();
}

void ObjectiveModel::onTransmissionAborted()
{
    qDebug() << "aborted";
    mTransmissionTimer.stop();
}

void ObjectiveModel::onTransmissionFinished()
{
    qDebug() << "finished";
    set_isDone(true);
}

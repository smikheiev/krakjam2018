#include <QDebug>

#include "objectivemodel.h"

ObjectiveModel::ObjectiveModel(QObject* parent):
    QObject(parent)
    , m_range(new RangeModel(this))
    , m_transmissionTime(3000)
    , m_posX(-1)
    , m_posY(-1)
    , m_isDone(false)
{
    range()->set_radius(15);

    mTransmissionTimer.setInterval(transmissionTime());
    mTransmissionTimer.setSingleShot(true);
    mTransmissionTimer.stop();

    connect(this, SIGNAL(posXChanged(int)), range(), SLOT(set_posX(int)));
    connect(this, SIGNAL(posYChanged(int)), range(), SLOT(set_posY(int)));

    connect(&mTransmissionTimer, SIGNAL(timeout()), this, SLOT(onTransmissionTimerTimeout()));
    connect(range(), SIGNAL(isTransmittingChanged(bool)), this, SLOT(onIsTransmittingChanged()));
}

void ObjectiveModel::onIsTransmittingChanged()
{
    if (range()->isTransmitting())
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

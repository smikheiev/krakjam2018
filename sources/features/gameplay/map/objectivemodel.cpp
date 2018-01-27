#include "objectivemodel.h"
#include "../constants.h"

ObjectiveModel::ObjectiveModel(QObject* parent):
    QObject(parent)
    , m_range(new RangeModel(this))
    , m_transmissionTime(3000)
    , m_posX(-1)
    , m_posY(-1)
    , m_isDone(false)
{
    range()->set_radius(OBJECTIVE_RANGE_RADIUS);

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
    mTransmissionTimer.start();
}

void ObjectiveModel::onTransmissionAborted()
{
    mTransmissionTimer.stop();
}

void ObjectiveModel::onTransmissionFinished()
{
    set_isDone(true);
}

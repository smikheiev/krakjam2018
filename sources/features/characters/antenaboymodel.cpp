#include <QDebug>
#include "antenaboymodel.h"
#include "../gameplay/constants.h"
#include "../koza.h"

int AntenaBoyModel::DistanceCounter = 0;

AntenaBoyModel::AntenaBoyModel(int id, int rangeRadius, int posX, int posY, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_boySize(ANTENA_BOY_SIZE)
    , m_posX(posX)
    , m_posY(posY)
    , m_moveX(0)
    , m_moveY(0)
    , m_isInactive(false)
    , m_isSelected(false)
    , m_range(new RangeModel(this))
{
    range()->set_radius(rangeRadius);

    makeInactiveTimer.setSingleShot(true);
    connect(&makeInactiveTimer, SIGNAL(timeout()), this, SLOT(onMakeInactiveTimerTimeout()));

    connect(this, SIGNAL(posXChanged(int)), this, SLOT(onPosChanged()));
    connect(this, SIGNAL(posYChanged(int)), this, SLOT(onPosChanged()));

    onPosChanged();
}

void AntenaBoyModel::moveKeyPressed(int keyPressed)
{
    if (isInactive()) return;
    if (keyPressed == Qt::Key_W || keyPressed == Qt::Key_Up) set_moveY(-1);
    if (keyPressed == Qt::Key_S || keyPressed == Qt::Key_Down) set_moveY(1);
    if (keyPressed == Qt::Key_A || keyPressed == Qt::Key_Left) set_moveX(-1);
    if (keyPressed == Qt::Key_D || keyPressed == Qt::Key_Right) set_moveX(1);
}

void AntenaBoyModel::moveKeyReleased(int keyReleased)
{
    if (isInactive()) return;
    if (keyReleased == Qt::Key_W || keyReleased == Qt::Key_Up) set_moveY(0);
    if (keyReleased == Qt::Key_S || keyReleased == Qt::Key_Down) set_moveY(0);
    if (keyReleased == Qt::Key_A || keyReleased == Qt::Key_Left) set_moveX(0);
    if (keyReleased == Qt::Key_D || keyReleased == Qt::Key_Right) set_moveX(0);
}

void AntenaBoyModel::makeInactiveForTime(int timeMs)
{
    set_isInactive(true);
    makeInactiveTimer.start(timeMs);

    set_moveX(0);
    set_moveY(0);
}

void AntenaBoyModel::onPosChanged()
{
    range()->set_posX(posX() - boySize() / 2);
    range()->set_posY(posY() - boySize() / 2);

    int xDist = qAbs(mLastPosX - posX());
    int yDist = qAbs(mLastPosY - posY());
    mLastPosX = posX();
    mLastPosY = posY();
    if (xDist > 20 || yDist > 20)
    {
        // A little hack, I know, why not :P
        return;
    }
    Koza::AddAntenaBoysDistance(xDist, yDist);
}

void AntenaBoyModel::onMakeInactiveTimerTimeout()
{
    set_isInactive(false);
}

#include "antenaboymodel.h"
#include "../gameplay/constants.h"

AntenaBoyModel::AntenaBoyModel(int id, int rangeRadius, int posX, int posY, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_boySize(ANTENA_BOY_SIZE)
    , m_posX(posX)
    , m_posY(posY)
    , m_isInactive(false)
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
    if (keyPressed == Qt::Key_W || keyPressed == Qt::Key_Up) moveY = -1;
    if (keyPressed == Qt::Key_S || keyPressed == Qt::Key_Down) moveY = 1;
    if (keyPressed == Qt::Key_A || keyPressed == Qt::Key_Left) moveX = -1;
    if (keyPressed == Qt::Key_D || keyPressed == Qt::Key_Right) moveX = 1;
}

void AntenaBoyModel::moveKeyReleased(int keyReleased)
{
    if (isInactive()) return;
    if (keyReleased == Qt::Key_W || keyReleased == Qt::Key_Up) moveY = 0;
    if (keyReleased == Qt::Key_S || keyReleased == Qt::Key_Down) moveY = 0;
    if (keyReleased == Qt::Key_A || keyReleased == Qt::Key_Left) moveX = 0;
    if (keyReleased == Qt::Key_D || keyReleased == Qt::Key_Right) moveX = 0;
}

void AntenaBoyModel::makeInactiveForTime(int timeMs)
{
    set_isInactive(true);
    makeInactiveTimer.start(timeMs);

    moveX = 0;
    moveY = 0;
}

void AntenaBoyModel::onPosChanged()
{
    range()->set_posX(posX() - boySize() / 2);
    range()->set_posY(posY() - boySize() / 2);
}

void AntenaBoyModel::onMakeInactiveTimerTimeout()
{
    set_isInactive(false);
}

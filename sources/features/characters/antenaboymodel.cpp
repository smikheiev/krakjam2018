#include "antenaboymodel.h"

AntenaBoyModel::AntenaBoyModel(QObject* parent)
    : QObject(parent)
    , m_boySize(15)
    , m_posX(0)
    , m_posY(0)
{
}

void AntenaBoyModel::moveKeyPressed(int keyPressed)
{
    if (keyPressed == Qt::Key_W || keyPressed == Qt::Key_Up) moveY = -1;
    if (keyPressed == Qt::Key_S || keyPressed == Qt::Key_Down) moveY = 1;
    if (keyPressed == Qt::Key_A || keyPressed == Qt::Key_Left) moveX = -1;
    if (keyPressed == Qt::Key_D || keyPressed == Qt::Key_Right) moveX = 1;
}

void AntenaBoyModel::moveKeyReleased(int keyReleased)
{
    if (keyReleased == Qt::Key_W || keyReleased == Qt::Key_Up) moveY = 0;
    if (keyReleased == Qt::Key_S || keyReleased == Qt::Key_Down) moveY = 0;
    if (keyReleased == Qt::Key_A || keyReleased == Qt::Key_Left) moveX = 0;
    if (keyReleased == Qt::Key_D || keyReleased == Qt::Key_Right) moveX = 0;
}

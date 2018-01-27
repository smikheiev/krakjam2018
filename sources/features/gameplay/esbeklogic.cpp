#include "esbeklogic.h"
#include "../../utils.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, CharactersLogic* charactersLogic, QObject *parent)
    : QObject(parent)
    , m_esbekModel(new EsbekModel(this))
    , mMapModel(mapModel)
    , mCharactersLogic(charactersLogic)
{
   esbekModel()->set_moveX(1);
}

void EsbekLogic::tryToCatchAntenaBoyToJail()
{
    for (int i = 0; i < mCharactersLogic->mAntenaBoyList.count(); ++i)
    {
        AntenaBoyModel* boy = mCharactersLogic->mAntenaBoyList.at(i);
        if (boy->isInactive()) continue;

        qreal distanse = Utils::distance(esbekModel()->posX(), esbekModel()->posY(), boy->posX(), boy->posY());
        if (distanse < esbekModel()->killRadius())
        {
            mCharactersLogic->catchedByEsbek(boy);
        }
    }
}

void EsbekLogic::moveEsbek()
{
    tryToCatchAntenaBoyToJail();

    if (esbekModel()->posX() % 30 != 0 || esbekModel()->posY() % 30 != 0) {
        setDirectionMove(lastDirection);
        return;
    }

    QVector<DIRECTION> allPossibleDirections = QVector<DIRECTION> {UP, DOWN, LEFT, RIGHT};
    QVector<DIRECTION> directionsToSelectRandom;
    for (int i=0; i<allPossibleDirections.count(); i++) {
        if (allPossibleDirections.at(i) == getOppositDirection(lastDirection)) continue;

        if (canMove(allPossibleDirections.at(i))) {
            directionsToSelectRandom.append(allPossibleDirections.at(i));
        }
    }

    DIRECTION directionToMove = DIRECTION::NONE;
    if (directionsToSelectRandom.size() == 0)
    {
        directionToMove = getOppositDirection(lastDirection);
    }
    else
    {
        int randomIndex = (qrand() % directionsToSelectRandom.count());
        directionToMove = directionsToSelectRandom.at(randomIndex);
    }

    setDirectionMove(directionToMove);
}

EsbekLogic::DIRECTION EsbekLogic::getOppositDirection(DIRECTION direction) {
    switch (direction) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
        default:
            return NONE;
    }
}

void EsbekLogic::setDirectionMove(DIRECTION directionMove)
{
    m_esbekModel->set_moveX(0);
    m_esbekModel->set_moveY(0);

    lastDirection = directionMove;

    int newPosX;
    int newPosY;
    switch (directionMove) {
        case LEFT:
            m_esbekModel->set_moveX(-1);
            newPosX = m_esbekModel->posX() - ESBEK_SPEED;
            if (newPosX < 0) {
                newPosX = 0;
            }
            m_esbekModel->set_posX(newPosX);
            break;
        case RIGHT:
            m_esbekModel->set_moveX(1);
            m_esbekModel->set_posX(m_esbekModel->posX() + ESBEK_SPEED);
            break;
        case UP:
            m_esbekModel->set_moveY(-1);
            newPosY = m_esbekModel->posY() - ESBEK_SPEED;
            if (newPosY < 0) {
                newPosY = 0;
            }
            m_esbekModel->set_posY(newPosY);
            break;
        case DOWN:
            m_esbekModel->set_moveY(1);
            m_esbekModel->set_posY(m_esbekModel->posY() + ESBEK_SPEED);
            break;
        default:
            qDebug() << "ERROR ERROR ERROR !!!!!!!!!!!!!!!!";
            break;
    }
}

bool EsbekLogic::canMove(DIRECTION direction) {
    switch (direction) {
        case UP:
            return canMoveUp();
        case DOWN:
            return canMoveDown();
        case RIGHT:
            return canMoveRight();
        case LEFT:
            return canMoveLeft();
        default:
            return false;
    }
}

bool EsbekLogic::canMoveUp()
{
    if (esbekModel()->posY() - ESBEK_SPEED < 0) return false;
    return mMapModel->tryToMove(esbekModel()->posX(), esbekModel()->posY() - ESBEK_SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveDown()
{
    return mMapModel->tryToMove(esbekModel()->posX(), esbekModel()->posY() + ESBEK_SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveLeft()
{
    if (esbekModel()->posX() - ESBEK_SPEED < 0) return false;
    return mMapModel->tryToMove(esbekModel()->posX() - ESBEK_SPEED, esbekModel()->posY(), TILE_SIZE);
}

bool EsbekLogic::canMoveRight()
{
    return mMapModel->tryToMove(esbekModel()->posX() + ESBEK_SPEED, esbekModel()->posY(), TILE_SIZE);
}


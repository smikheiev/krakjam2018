#include "esbeklogic.h"
#include "../../utils.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_esbekModel(new EsbekModel(this))
    , m_mapModel(mapModel)
{
   esbekModel()->set_moveX(1);
}

void EsbekLogic::setAntenaBoyList(QList<AntenaBoyModel *>* antenaBoyList)
{
    mAntenaBoyList = antenaBoyList;
}

void EsbekLogic::searchAntenaBoyToJail()
{
    // TODO
//    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
//    for (int i=0; mAntenaBoyList->size()-1; i++) {
//        qreal distanceValue = Utils::distance(esbekModel()->posX(), esbekModel()->posY(), mAntenaBoyList->at(i)->posX(), mAntenaBoyList->at(i)->posY());
//        int range =
    //    }
}

void EsbekLogic::moveEsbek()
{
    searchAntenaBoyToJail();

    if (esbekModel()->posX() % 30 != 0 || esbekModel()->posY() % 30 != 0) {
        setDirectionMove(lastDirection);
        return;
    }

    QVector<DIRECTION> possibleDirections = QVector<DIRECTION> {NORTH, SOUTH, WEST, EAST};
    possibleDirections.remove(getOppositDirection(lastDirection));
    QVector<DIRECTION> moves;
    for (int i=0; i<possibleDirections.count(); i++) {
        if (canMove(possibleDirections.at(i))) {
            moves.append(possibleDirections.at(i));
        }
    }

    if (moves.size() == 0)
    {
        setDirectionMove(getOppositDirection(lastDirection));
        return;
    }
    else if (moves.size() == 1 && moves[0] == lastDirection)
    {
        setDirectionMove(lastDirection);
        return;
    }
    else if (moves.size() == 1 && moves[0] != lastDirection)
    {
        moves.append(getOppositDirection(lastDirection));
    }

    int randomIndex = (qrand() % moves.count());
    qDebug() << "moves.cont " << moves.size() << " RAND " << randomIndex;

    for(int i=0; i<moves.size(); i++) {
        qDebug() << "moves.at " << i << " ----> " << moves.at(i);
    }

    setDirectionMove(moves.at(randomIndex));
}

EsbekLogic::DIRECTION EsbekLogic::getOppositDirection(DIRECTION direction) {
    switch (direction) {
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case EAST:
            return WEST;
        case WEST:
            return EAST;
    }
    return SOUTH;
}

#include <QDebug>
void EsbekLogic::setDirectionMove(DIRECTION directionMove)
{
    m_esbekModel->set_moveX(0);
    m_esbekModel->set_moveY(0);

    lastDirection = directionMove;

    int newPosX;
    int newPosY;
    switch (directionMove) {
        case WEST:
            m_esbekModel->set_moveX(-1);
            newPosX = m_esbekModel->posX() - SPEED;
            if (newPosX < 0) {
                newPosX = 0;
            }
            m_esbekModel->set_posX(newPosX);
            break;
        case EAST:
            m_esbekModel->set_moveX(1);
            m_esbekModel->set_posX(m_esbekModel->posX() + SPEED);
            break;
        case NORTH:
            m_esbekModel->set_moveY(-1);
            newPosY = m_esbekModel->posY() - SPEED;
            if (newPosY < 0) {
                newPosY = 0;
            }
            m_esbekModel->set_posY(newPosY);
            break;
        case SOUTH:
            m_esbekModel->set_moveY(1);
            m_esbekModel->set_posY(m_esbekModel->posY() + SPEED);
            break;
        default:
            break;
    }
}

bool EsbekLogic::canMove(DIRECTION direction) {
    switch (direction) {
        case NORTH:
            return canMoveNorth();
        case SOUTH:
            return canMoveSouth();
        case EAST:
            return canMoveEast();
        case WEST:
            return canMoveWest();
    }
    return false;
}

bool EsbekLogic::canMoveNorth()
{
    if (esbekModel()->posY() - SPEED < 0) return false;
    return mapModel()->tryToMove(esbekModel()->posX(), esbekModel()->posY() - SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveSouth()
{
    return mapModel()->tryToMove(esbekModel()->posX(), esbekModel()->posY() + SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveEast()
{
    if (esbekModel()->posX() - SPEED < 0) return false;
    return mapModel()->tryToMove(esbekModel()->posX() - SPEED, esbekModel()->posY(), TILE_SIZE);
}

bool EsbekLogic::canMoveWest()
{
    return mapModel()->tryToMove(esbekModel()->posX() + SPEED, esbekModel()->posY(), TILE_SIZE);
}


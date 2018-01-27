#include "esbeklogic.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_esbekModel(new EsbekModel(this))
    , m_mapModel(mapModel)
{
   timer.setInterval(300);
   timer.setSingleShot(false);

   connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
   esbekModel()->set_moveX(1);
   timer.start();
}

void EsbekLogic::onTimeout()
{
    if (m_esbekModel->moveX() == 1) {
        checkDirection(WEST);
    } else if (m_esbekModel->moveX() == -1) {
        checkDirection(EAST);
    } else if (m_esbekModel->moveY() == 1) {
        checkDirection(NORTH);
    } else if (m_esbekModel->moveY() == -1) {
        checkDirection(SOUTH);
    }
}

void EsbekLogic::checkDirection(DIRECTION from)
{
    QVector<DIRECTION> possibleDirections = QVector<DIRECTION> {NORTH, SOUTH, WEST, EAST};
    possibleDirections.removeOne(from);

    QVector<DIRECTION> moves;
    for (int i = 0; i < possibleDirections.count(); i++ ) {
        switch (possibleDirections.at(i)) {
            case NORTH:
                if (canMoveNorth())
                    moves.append(NORTH);
                break;
            case SOUTH:
                if (canMoveSouth())
                    moves.append(SOUTH);
                break;
            case EAST:
                if (canMoveEast())
                    moves.append(EAST);
                break;
            case WEST:
                if (canMoveWest())
                    moves.append(WEST);
                break;
        }
    }

    DIRECTION direction;
    if (moves.count() == 0) {
        direction = from;
    } else {
        int randomIndex = (qrand() % moves.count());
        direction = moves.at(randomIndex);
    }

    setDirectionMove(direction);
}

void EsbekLogic::setDirectionMove(EsbekLogic::DIRECTION directionMove)
{
    m_esbekModel->set_moveX(0);
    m_esbekModel->set_moveY(0);

    int row = m_esbekModel->row();
    int column = m_esbekModel->column();

    switch (directionMove) {
        case WEST:
            m_esbekModel->set_moveX(-1);
            m_esbekModel->set_row(row - 1);
            break;
        case EAST:
            m_esbekModel->set_moveX(1);
            m_esbekModel->set_row(row + 1);
            break;
        case NORTH:
            m_esbekModel->set_moveY(-1);
            m_esbekModel->set_column(column - 1);
            break;
        case SOUTH:
            m_esbekModel->set_moveY(1);
            m_esbekModel->set_column(column + 1);
            break;
        default:
            break;
    }
}

bool EsbekLogic::canMoveNorth()
{
    return m_esbekModel->column() > 0 && m_mapModel->getTileByposition(m_esbekModel->row(), m_esbekModel->column() - 1)->tileType() == TileType::Street;
}

bool EsbekLogic::canMoveSouth()
{
    return m_esbekModel->column() < m_mapModel->height() - 1 && m_mapModel->getTileByposition(m_esbekModel->row(), m_esbekModel->column() + 1)->tileType() == TileType::Street;
}

bool EsbekLogic::canMoveEast()
{
    return m_esbekModel->row() < m_mapModel->width() - 1 && m_mapModel->getTileByposition(m_esbekModel->row() + 1, m_esbekModel->column())->tileType() == TileType::Street;
}

bool EsbekLogic::canMoveWest()
{
    return m_esbekModel->row() > 0 && m_mapModel->getTileByposition(m_esbekModel->row() - 1, m_esbekModel->column())->tileType() == TileType::Street;
}


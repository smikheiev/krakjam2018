#include "esbeklogic.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_esbekModel(new EsbekModel(this))
    , m_mapModel(mapModel)
{
   timer.setInterval(1000);
   timer.setSingleShot(false);

   connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
   esbekModel()->set_moveX(1);
   timer.start();
}

void EsbekLogic::onTimeout()
{
    int row = m_esbekModel->row();
    int column = m_esbekModel->column();

    qDebug() << "current: [" << row << "," << column << " ], current tile: " << m_mapModel->getTileByposition(row, column)->tileType();
    QString moves = "";

    if (m_esbekModel->moveX() == 1) {
        if (row + 1 < m_mapModel->width()
            && m_mapModel->getTileByposition(row + 1, column)->tileType() == TileType::Street) {
            esbekModel()->set_row(row + 1);
        } else {
            qDebug() << "random new direction from moveX 1";
            setNewDirection();
        }
    } else if (m_esbekModel->moveX() == -1) {
        if (row - 1 > 0
            && m_mapModel->getTileByposition(row - 1, column)->tileType() == TileType::Street) {
            esbekModel()->set_row(row - 1);
        } else {
            qDebug() << "random new direction from moveX -1";
            setNewDirection();
        }
    } else if (m_esbekModel->moveY() == 1) {
        if (column + 1 < m_mapModel->height()
            && m_mapModel->getTileByposition(row, column + 1)->tileType() == TileType::Street) {
            esbekModel()->set_column(column + 1);
        } else {
            qDebug() << "random new direction from moveX -1";
            setNewDirection();
        }
    } else if (m_esbekModel->moveY() == -1) {
        if (column - 1 > 0
            && m_mapModel->getTileByposition(row, column - 1)->tileType() == TileType::Street) {
            esbekModel()->set_column(column - 1);
        } else {
            qDebug() << "random new direction from moveY -1";
            setNewDirection();
        }
    }


}

void EsbekLogic::setNewDirection()
{
    m_esbekModel->set_moveX(0);
    m_esbekModel->set_moveY(0);

    int row = m_esbekModel->row();
    int column = m_esbekModel->column();
    QVector<DIRECTION> moves;
    if (column > 0 && m_mapModel->getTileByposition(row, column - 1)->tileType() == TileType::Street) {
        moves.append(NORTH);
    }
    if (column < m_mapModel->height() - 1 && m_mapModel->getTileByposition(row, column + 1)->tileType() == TileType::Street) {
        moves.append(SOUTH);
    }
    if (row < m_mapModel->width() - 1 && m_mapModel->getTileByposition(row + 1, column)->tileType() == TileType::Street) {
        moves.append(EAST);
    }
    if (row > 0 && m_mapModel->getTileByposition(row - 1, column)->tileType() == TileType::Street) {
        moves.append(WEST);
    }

    int randomIndex = (qrand() % moves.count());
    DIRECTION direction = moves.at(randomIndex);

    qDebug() << "DIRECTION: " << direction;
    switch (direction) {
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

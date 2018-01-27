#include <QDebug>

#include "mapmodel.h"
#include "../constants.h"

MapModel::MapModel(QObject *parent)
    : QObject(parent)
    , m_tileSize(TILE_SIZE)
    , m_width(15)
    , m_height(10)
    , m_count(m_width * m_height)
{
    initTiles();
}

TileModel *MapModel::getTileByIndex(const int tileIndex)
{
    int column = getColumnByIndex(tileIndex);
    int row = getRowByIndex(tileIndex);

    TileModel* tileModel = mTiles.at(row)->at(column);
    return tileModel;
}

TileType MapModel::getTileType(int posX, int posY)
{
    if (posY / tileSize() > mTiles.size() - 1) return TileType::None;
    if (posX / tileSize() > mTiles.at(posY / tileSize())->size() - 1) return TileType::None;
    return mTiles.at(posY / tileSize())->at(posX / tileSize())->tileType();
}

TileModel *MapModel::getTileByposition(const int column, const int row)
{
    TileModel* tileModel = mTiles.at(row)->at(column);
    return tileModel;
}

bool MapModel::tryToMove(int posX, int posY, int boySize)
{
    if (!TileTypeEnumWrapper::isStreet(getTileType(posX, posY))) return false;
    if (!TileTypeEnumWrapper::isStreet(getTileType(posX + boySize - 1, posY))) return false;
    if (!TileTypeEnumWrapper::isStreet(getTileType(posX, posY + boySize - 1))) return false;
    if (!TileTypeEnumWrapper::isStreet(getTileType(posX + boySize - 1, posY + boySize - 1))) return false;
    return true;
}

QPoint MapModel::getStartAntenaBoyPosition()
{
    for (int i = 0; i < width(); ++i)
    {
        for (int j = 0; j < height(); ++j)
        {
            TileModel* tile = mTiles.at(j)->at(i);
            if (tile->tileType() == TileType::Headquarter)
            {
                return QPoint(i, j + 1);
            }
        }
    }
    return QPoint(0, 0);
}

void MapModel::initTiles()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{200, 200, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 200, 200});
    tileTypes.append(QVector<int>{200, 11, 11, 11, 11, 11, 11, 32, 42, 42, 42, 34, 11, 11, 200});
    tileTypes.append(QVector<int>{11, 11, 11, 11, 32, 42, 42, 24, 15, 11, 15, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 32, 42, 42, 24, 11, 15, 31, 42, 22, 11, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 15, 11, 41, 11, 11, 11, 11, 41, 11, 41, 15, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 11, 32, 21, 42, 42, 10, 42, 21, 42, 21, 42, 34, 11});
    tileTypes.append(QVector<int>{11, 31, 42, 24, 11, 11, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{11, 11, 11, 31, 42, 34, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{200, 11, 11, 11, 11, 31, 42, 21, 42, 42, 42, 42, 42, 33, 11});
    tileTypes.append(QVector<int>{200, 200, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 200});

    for (int i = 0; i < height(); ++i)
    {
        for (int j = 0; j < width(); ++j)
        {
            int tileTypeInt = tileTypes.value(i).value(j);
            TileType tileType = static_cast<TileType>(tileTypeInt);

            TileModel* tileModel = new TileModel(this);
            tileModel->set_tileType(tileType);
            tileModel->set_posX((j + 0.5)* tileSize());
            tileModel->set_posY((i + 0.5)* tileSize());

            if (mTiles.count() == i)
            {
                mTiles.append(new QVector<TileModel*>());
            }

            mTiles.at(i)->insert(j, tileModel);
        }
    }
}

int MapModel::getColumnByIndex(int index) const
{
    return index % width();
}

int MapModel::getRowByIndex(int index) const
{
    return (int)(index / width());
}

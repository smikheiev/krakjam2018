#include <QDebug>

#include "mapmodel.h"
#include "../constants.h"

MapModel::MapModel(QObject *parent)
    : QObject(parent)
    , m_tileSize(TILE_SIZE)
    , m_width(10)
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

#include <QDebug>
bool MapModel::tryToMove(int posX, int posY, int boySize)
{
    if (getTileType(posX, posY) != TileType::Street) return false;
    if (getTileType(posX + boySize - 1, posY) != TileType::Street) return false;
    if (getTileType(posX, posY + boySize - 1) != TileType::Street) return false;
    if (getTileType(posX + boySize - 1, posY + boySize - 1) != TileType::Street) return false;
    return true;
}

void MapModel::initTiles()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{2,2,2,2,2,2,2,2,2,3});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,4,4,4,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,4,4,4,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,4,4,4,2});
    tileTypes.append(QVector<int>{2,2,2,2,1,2,2,2,2,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,2,4,4,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,2,2,4,4,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,4,4,4,2});
    tileTypes.append(QVector<int>{2,4,4,4,2,4,4,4,4,2});
    tileTypes.append(QVector<int>{2,2,2,2,2,2,2,2,2,2});

    for (int i = 0; i < width(); ++i)
    {
        for (int j = 0; j < height(); ++j)
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

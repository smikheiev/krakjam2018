#include <QDebug>

#include "mapmodel.h"

MapModel::MapModel(QObject *parent)
    : QObject(parent)
    , m_width(10)
    , m_height(10)
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

void MapModel::initTiles()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{1,2,3,1,2,3,1,2,3,1});
    tileTypes.append(QVector<int>{2,3,1,2,3,1,2,3,1,2});
    tileTypes.append(QVector<int>{3,1,2,3,1,2,3,1,2,3});
    tileTypes.append(QVector<int>{1,2,3,1,2,3,1,2,3,1});
    tileTypes.append(QVector<int>{2,3,1,2,3,1,2,3,1,2});
    tileTypes.append(QVector<int>{3,1,2,3,1,2,3,1,2,3});
    tileTypes.append(QVector<int>{1,2,3,1,2,3,1,2,3,1});
    tileTypes.append(QVector<int>{2,3,1,2,3,1,2,3,1,2});
    tileTypes.append(QVector<int>{3,1,2,3,1,2,3,1,2,3});
    tileTypes.append(QVector<int>{1,2,3,1,2,3,1,2,3,1});

    for (int i = 0; i < width(); ++i)
    {
        for (int j = 0; j < height(); ++j)
        {
            int tileTypeInt = tileTypes.value(i).value(j);
            TileType tileType = static_cast<TileType>(tileTypeInt);

            TileModel* tileModel = new TileModel(this);
            tileModel->set_tileType(tileType);

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

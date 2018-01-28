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
    initTiles(2);

    set_height(mTiles.count());
    set_width(mTiles.at(0)->count());
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

QPoint MapModel::getHQPosition()
{
    for (int i = 0; i < width(); ++i)
    {
        for (int j = 0; j < height(); ++j)
        {
            TileModel* tile = mTiles.at(j)->at(i);
            if (tile->tileType() == TileType::Headquarter)
            {
                return QPoint(i, j);
            }
        }
    }
    return QPoint(0, 0);
}

QPoint MapModel::getRandomEsbekStartPosition()
{
    QVector<QPoint> possibleStartPositions;
    QPoint hqPosition = getHQPosition();
    for (int i = 0; i < width(); ++i)
    {
        for (int j = 0; j < height(); ++j)
        {
            bool isNearHQx = qAbs(hqPosition.x() - i) <= 1;
            bool isNearHQy = qAbs(hqPosition.y() - j) <= 1;

            if (isNearHQx || isNearHQy) continue;

            TileModel* tile = mTiles.at(j)->at(i);
            if (TileTypeEnumWrapper::isStreet(tile->tileType()))
            {
                possibleStartPositions.append(QPoint(i, j));
            }
        }
    }
    int randIndex = qrand() % possibleStartPositions.count();
    return possibleStartPositions.at(randIndex);
}

void MapModel::initTiles(int mapNumber)
{
    QVector<QVector<int>> tileTypes;
    switch (mapNumber) {
    case 2:
        tileTypes = getTilesForMap2();
        break;
    case 3:
        tileTypes = getTilesForMap3();
        break;
    default:
        tileTypes = getTilesForMap1();
        break;
    }

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

QVector<QVector<int> > MapModel::getTilesForMap1()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 90, 90});
    tileTypes.append(QVector<int>{90, 11, 11, 11, 11, 11, 11, 32, 42, 42, 42, 34, 11, 11, 90});
    tileTypes.append(QVector<int>{11, 11, 11, 11, 32, 42, 42, 24, 15, 11, 15, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 32, 42, 42, 24, 11, 15, 31, 42, 22, 11, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 15, 11, 41, 11, 11, 11, 11, 41, 11, 41, 15, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 11, 32, 21, 42, 42, 10, 42, 21, 42, 21, 42, 34, 11});
    tileTypes.append(QVector<int>{11, 31, 42, 24, 11, 11, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{11, 11, 11, 31, 42, 34, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{90, 11, 11, 11, 11, 31, 42, 21, 42, 42, 42, 42, 42, 33, 11});
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 90});
    return tileTypes;
}

QVector<QVector<int> > MapModel::getTilesForMap2()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 41, 11, 41, 11, 11, 11, 90, 90});
    tileTypes.append(QVector<int>{90, 11, 15, 11, 11, 32, 42, 20, 42, 20, 42, 22, 42, 15, 90});
    tileTypes.append(QVector<int>{11, 42, 34, 15, 32, 33, 15, 41, 11, 41, 15, 41, 15, 41, 11});
    tileTypes.append(QVector<int>{11, 11, 23, 42, 24, 11, 42, 21, 42, 11, 11, 23, 42, 24, 11});
    tileTypes.append(QVector<int>{11, 32, 33, 11, 31, 34, 11, 11, 11, 41, 11, 41, 15, 41, 11});
    tileTypes.append(QVector<int>{11, 41, 15, 24, 15, 31, 34, 10, 32, 21, 22, 21, 42, 24, 11});
    tileTypes.append(QVector<int>{11, 41, 11, 24, 11, 11, 31, 22, 33, 11, 41, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{11, 31, 42, 20, 42, 34, 11, 41, 11, 32, 33, 15, 32, 33, 11});
    tileTypes.append(QVector<int>{90, 11, 15, 31, 11, 31, 42, 21, 42, 33, 15, 42, 33, 11, 11});
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 90});
    return tileTypes;
}

QVector<QVector<int> > MapModel::getTilesForMap3()
{
    QVector<QVector<int>> tileTypes;
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 90, 90});
    tileTypes.append(QVector<int>{90, 11, 11, 11, 11, 11, 11, 32, 42, 42, 42, 34, 11, 11, 90});
    tileTypes.append(QVector<int>{11, 11, 11, 11, 32, 42, 42, 24, 15, 11, 15, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 32, 42, 42, 24, 11, 11, 31, 42, 22, 11, 41, 11, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 15, 11, 41, 11, 11, 11, 11, 41, 11, 41, 15, 11, 11});
    tileTypes.append(QVector<int>{11, 41, 11, 32, 21, 42, 11, 10, 11, 21, 42, 21, 42, 34, 11});
    tileTypes.append(QVector<int>{11, 31, 42, 24, 11, 11, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{11, 11, 11, 31, 42, 34, 11, 41, 11, 11, 11, 11, 11, 41, 11});
    tileTypes.append(QVector<int>{90, 11, 11, 11, 11, 31, 42, 21, 42, 42, 42, 42, 42, 33, 11});
    tileTypes.append(QVector<int>{90, 90, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 90});
    return tileTypes;
}

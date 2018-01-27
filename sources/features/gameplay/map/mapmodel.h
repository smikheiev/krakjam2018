#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QObject>
#include <QVector>

#include "../../../macros.h"
#include "tilemodel.h"

class MapModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, tileSize)

    AUTO_Q_PROPERTY(int, width)
    AUTO_Q_PROPERTY(int, height)
    AUTO_Q_PROPERTY(int, count)

public:
    explicit MapModel(QObject *parent = nullptr);

public:
    Q_INVOKABLE TileModel* getTileByIndex(const int tileIndex);

    TileType getTileType(int posX, int posY);

private:
    void initTiles();
    int getColumnByIndex(int index) const;
    int getRowByIndex(int index) const;

private:
    QVector<QVector<TileModel*>*> mTiles;
};

#endif // MAPMODEL_H

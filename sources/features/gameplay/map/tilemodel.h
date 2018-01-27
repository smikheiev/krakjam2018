#ifndef TILEMODEL_H
#define TILEMODEL_H

#include <QObject>

#include "../../../macros.h"
#include "tiletype.h"

class TileModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, posX) // pozycja srodka tila, zeby latwiej bylo liczyc "range"
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(TileType, tileType)

public:
    explicit TileModel(QObject *parent = nullptr);
};

#endif // TILEMODEL_H

#ifndef ANTENABOYMODEL_H
#define ANTENABOYMODEL_H

#include <QObject>

#include "../../macros.h"
#include "../gameplay/map/mapmodel.h"
#include "../gameplay/range/rangemodel.h"

class AntenaBoyModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, boySize)
    AUTO_Q_PROPERTY_CONSTANT(RangeModel*, range)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)

public:
    AntenaBoyModel(int rangeRadius, QObject* parent = nullptr);

    void moveKeyPressed(int keyPressed);
    void moveKeyReleased(int keyReleased);

    int moveX = 0; // -1 = left, 0 = nothing, 1 = right
    int moveY = 0; // -1 = up, 0 = nothing, 1 = down
};

#endif // ANTENABOYMODEL_H

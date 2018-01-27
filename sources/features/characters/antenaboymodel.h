#ifndef ANTENABOYMODEL_H
#define ANTENABOYMODEL_H

#include <QObject>
#include <QTimer>

#include "../../macros.h"
#include "../gameplay/map/mapmodel.h"
#include "../gameplay/range/rangemodel.h"

class AntenaBoyModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, id)

    AUTO_Q_PROPERTY_CONSTANT(int, boySize)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(int, moveX) // -1 = left, 0 = nothing, 1 = right
    AUTO_Q_PROPERTY(int, moveY) // -1 = up, 0 = nothing, 1 = down

    AUTO_Q_PROPERTY(bool, isInactive)

    AUTO_Q_PROPERTY_CONSTANT(RangeModel*, range)

public:
    AntenaBoyModel(int id, int rangeRadius, int posX = 0, int posY = 0, QObject* parent = nullptr);

    void moveKeyPressed(int keyPressed);
    void moveKeyReleased(int keyReleased);

    void makeInactiveForTime(int timeMs);

private slots:
    void onPosChanged();
    void onMakeInactiveTimerTimeout();

private:
    QTimer makeInactiveTimer;
};

#endif // ANTENABOYMODEL_H

#ifndef ESBEKMODEL_H
#define ESBEKMODEL_H

#include <QObject>

#include "../../macros.h"
#include "range/rangemodel.h"

class EsbekModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, id)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(int, moveX)
    AUTO_Q_PROPERTY(int, moveY)

    AUTO_Q_PROPERTY_CONSTANT(int, killRadius)
    AUTO_Q_PROPERTY_CONSTANT(int, seenRadius)

public:
    explicit EsbekModel(int id, QObject *parent = nullptr);

    enum DIRECTION {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        RIGHT = 3,
        LEFT = 4
    };

    DIRECTION lastDirection = DIRECTION::NONE;
};

#endif // ESBEKMODEL_H

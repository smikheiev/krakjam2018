#ifndef ESBEKLOGIC_H
#define ESBEKLOGIC_H

#include <QObject>
#include <QTimer>

#include "../../macros.h"
#include "esbekmodel.h"
#include "map/mapmodel.h"

class EsbekLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(EsbekModel*, esbekModel)
    AUTO_Q_PROPERTY(MapModel*, mapModel)

public:
    explicit EsbekLogic(MapModel* mapModel, QObject *parent = nullptr);

    enum DIRECTION {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST
    };

private:
    QTimer timer;

private slots:
    void onTimeout();
    void setNewDirection();
};

#endif // ESBEKLOGIC_H

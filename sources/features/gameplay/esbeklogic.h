#ifndef ESBEKLOGIC_H
#define ESBEKLOGIC_H

#include <QObject>
#include <QTimer>
#include <QList>

#include "../../macros.h"
#include "esbekmodel.h"
#include "map/mapmodel.h"
#include "../characters/antenaboymodel.h"

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

    static const int TILE_SIZE = 30;
    static const int SPEED = 1;

    Q_INVOKABLE void moveEsbek();
    void setAntenaBoyList(QList<AntenaBoyModel*>* antenaBoyList);

private:
    QList<AntenaBoyModel*>* mAntenaBoyList;
    DIRECTION lastDirection = DIRECTION::SOUTH;

    void searchAntenaBoyToJail();

private slots:
    void setDirectionMove(DIRECTION directionMove);
    DIRECTION getOppositDirection(DIRECTION direction);
    bool canMove(DIRECTION direction);
    bool canMoveNorth();
    bool canMoveSouth();
    bool canMoveEast();
    bool canMoveWest();
};

#endif // ESBEKLOGIC_H

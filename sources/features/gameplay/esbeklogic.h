#ifndef ESBEKLOGIC_H
#define ESBEKLOGIC_H

#include <QObject>
#include <QTimer>
#include <QList>

#include "../../macros.h"
#include "esbekmodel.h"
#include "map/mapmodel.h"
#include "../characters/characterslogic.h"
#include "constants.h"

class EsbekLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(EsbekModel*, esbekModel)

public:
    explicit EsbekLogic(MapModel* mapModel, CharactersLogic* charactersLogic, QObject *parent = nullptr);

    enum DIRECTION {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        RIGHT = 3,
        LEFT = 4
    };

    Q_INVOKABLE void moveEsbek();

private:
    MapModel* mMapModel;
    CharactersLogic* mCharactersLogic;
    DIRECTION lastDirection = DIRECTION::NONE;

    void tryToCatchAntenaBoyToJail();

private slots:
    void setDirectionMove(DIRECTION directionMove);
    DIRECTION getOppositDirection(DIRECTION direction);
    bool canMove(DIRECTION direction);
    bool canMoveUp();
    bool canMoveDown();
    bool canMoveRight();
    bool canMoveLeft();
};

#endif // ESBEKLOGIC_H

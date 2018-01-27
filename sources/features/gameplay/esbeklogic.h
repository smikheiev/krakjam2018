#ifndef ESBEKLOGIC_H
#define ESBEKLOGIC_H

#include <QObject>
#include <QTimer>
#include <QList>

#include "../../macros.h"
#include "esbekmodel.h"
#include "map/mapmodel.h"
#include "../characters/antenaboymodel.h"
#include "constants.h"

class EsbekLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(EsbekModel*, esbekModel)
    AUTO_Q_PROPERTY(MapModel*, mapModel)

public:
    explicit EsbekLogic(MapModel* mapModel, QObject *parent = nullptr);

    enum DIRECTION {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        RIGHT = 3,
        LEFT = 4
    };

    Q_INVOKABLE void moveEsbek();
    void setAntenaBoyList(QList<AntenaBoyModel*>* antenaBoyList);

private:
    QList<AntenaBoyModel*>* mAntenaBoyList;
    DIRECTION lastDirection = DIRECTION::NONE;

    void searchAntenaBoyToJail();

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

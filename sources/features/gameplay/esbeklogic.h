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

    AUTO_Q_PROPERTY(QVariantList, esbekList)

public:
    explicit EsbekLogic(MapModel* mapModel, CharactersLogic* charactersLogic, QObject *parent = nullptr);

    Q_INVOKABLE void moveEsbek();

    void resetEsbeks();

public slots:
    void onObjectiveCompleted();

signals:
    void esbekCatchAntenaBoy();

private:
    MapModel* mMapModel;
    CharactersLogic* mCharactersLogic;

    QList<EsbekModel*> mEsbekModelsList;

    int objectiveCompletedCnt = 0;

    void createEsbeks();
    void addEsbek(QPoint startPoint);
    void updateVariantList();

    void tryToCatchAntenaBoyToJail();
    void setEsbekToStartPosition(EsbekModel *esbek, int startX, int startY);
    void moveEsbek(EsbekModel* esbekModel);

private slots:
    void setDirectionMove(EsbekModel* esbekModel, EsbekModel::DIRECTION directionMove);
    EsbekModel::DIRECTION getOppositDirection(EsbekModel::DIRECTION direction);
    bool canMove(EsbekModel* esbekModel, EsbekModel::DIRECTION direction);
    bool canMoveUp(EsbekModel* esbekModel);
    bool canMoveDown(EsbekModel* esbekModel);
    bool canMoveRight(EsbekModel* esbekModel);
    bool canMoveLeft(EsbekModel* esbekModel);
};

#endif // ESBEKLOGIC_H

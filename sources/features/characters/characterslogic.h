#ifndef CHARACTERSLOGIC_H
#define CHARACTERSLOGIC_H

#include "../../macros.h"
#include "antenaboymodel.h"
#include "../gameplay/map/mapmodel.h"

#include <QObject>
#include <QVariantList>

class CharactersLogic : public QObject
{
public:
    CharactersLogic(MapModel* mMapModel, QObject* parent = nullptr);

    Q_OBJECT

    AUTO_Q_PROPERTY(QVariantList, antenaBoyList)

public:
    void changSelectedAntenaBoy(int antenaBoySelected);
    void selectAntenaBoy(int id);
    void moveKeyPressed(int keyPressed);
    void moveKeyReleased(int keyReleased);
    Q_INVOKABLE void move();

    bool canMoveOnPosition(int posX, int posY);
    QList<AntenaBoyModel*> mAntenaBoyList;

    void catchedByEsbek(AntenaBoyModel* boy);
    void restartPositionsAllAntenaBoys();

private:
    int antenaBoySelected = -1;

    AntenaBoyModel* getAntenaBoySelected();
    void setBoyToStartPosition(AntenaBoyModel* boy);

    MapModel* mMapModel;
};

#endif // CHARACTERSLOGIC_H

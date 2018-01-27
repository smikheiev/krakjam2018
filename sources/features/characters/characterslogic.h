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
    CharactersLogic(QObject* parent);

    Q_OBJECT

    AUTO_Q_PROPERTY(QVariantList, antenaBoyList)

public:
    void changSelectedAntenaBoy(int antenaBoySelected);
    void moveKeyPressed(int keyPressed);
    void moveKeyReleased(int keyReleased);
    Q_INVOKABLE void move();

    void setMapModel(MapModel* mapModel);

    bool tryToMove(int posX, int posY, int boySize);
    bool canMoveOnPosition(int posX, int posY);

    QList<AntenaBoyModel*> mAntenaBoyModel;

private:
    int antenaBoySelected = 0;

    AntenaBoyModel* getAntenaBoySelected();

    MapModel* mapModel;
};

#endif // CHARACTERSLOGIC_H

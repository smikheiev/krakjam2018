#include <QDebug>
#include <QPoint>
#include "characterslogic.h"
#include "../gameplay/constants.h"

CharactersLogic::CharactersLogic(MapModel* mapModel, QObject* parent)
    : QObject(parent)
    , mMapModel(mapModel)
{
    for (int i = 0; i < 3; ++i)
    {
        AntenaBoyModel* boy = new AntenaBoyModel(i, ANTENA_BOY_RANGE_RADIUS, 0, 0, this);
        setBoyToStartPosition(boy);
        mAntenaBoyList.append(boy);
    }

    QVariantList vl;
    for (int i = 0; i < mAntenaBoyList.count(); ++i)
    {
        vl.append(QVariant::fromValue(mAntenaBoyList.at(i)));
    }
    set_antenaBoyList(vl);
}

void CharactersLogic::changSelectedAntenaBoy(int keyPressed)
{
    getAntenaBoySelected()->moveKeyReleased(Qt::Key_Up); // haczorek
    getAntenaBoySelected()->moveKeyReleased(Qt::Key_Left);

    if (keyPressed == Qt::Key_1) antenaBoySelected = 0;
    if (keyPressed == Qt::Key_2) antenaBoySelected = 1;
    if (keyPressed == Qt::Key_3) antenaBoySelected = 2;
}

void CharactersLogic::moveKeyPressed(int keyPressed)
{
    getAntenaBoySelected()->moveKeyPressed(keyPressed);
}

void CharactersLogic::moveKeyReleased(int keyReleased)
{
    getAntenaBoySelected()->moveKeyReleased(keyReleased);
}

void CharactersLogic::catchedByEsbek(AntenaBoyModel *boy)
{
    boy->makeInactiveForTime(2000);
    setBoyToStartPosition(boy);
}

AntenaBoyModel* CharactersLogic::getAntenaBoySelected() {
    return mAntenaBoyList.at(antenaBoySelected);
}

void CharactersLogic::setBoyToStartPosition(AntenaBoyModel *boy)
{
    QPoint startPosition = mMapModel->getHQPosition();
    int posX = startPosition.x() * TILE_SIZE + (TILE_SIZE - ANTENA_BOY_SIZE) / 2;
    int posY = (startPosition.y() + 1) * TILE_SIZE + (TILE_SIZE - ANTENA_BOY_SIZE) / 2;

    boy->set_posX(posX);
    boy->set_posY(posY);
}

void CharactersLogic::move() {
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (antenaBoy->moveX == 0 && antenaBoy->moveY == 0) continue;

        float newX = antenaBoy->posX() + ANTENA_BOY_SPEED * antenaBoy->moveX;
        if (newX < 0) newX = 0;

        float newY = antenaBoy->posY() + ANTENA_BOY_SPEED * antenaBoy->moveY;
        if (newY < 0) newY = 0;

        if (!mMapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX(); // jesli sie nie da sprobuj sie ruszyc tylko w pionie
        }

        if (!mMapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX() + ANTENA_BOY_SPEED * antenaBoy->moveX;
            if (newX < 0) newX = 0;
            newY = antenaBoy->posY(); // jesli sie nie da sprobuj sie ruszyc tylko w poziomie
        }

        if (!mMapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            continue; // jesli sie nie da no to chu...
        }

        antenaBoy->set_posX(newX);
        antenaBoy->set_posY(newY);
    }
}


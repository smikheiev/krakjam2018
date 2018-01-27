#include "characterslogic.h"

CharactersLogic::CharactersLogic(QObject* parent)
    : QObject(parent)
{
    mAntenaBoyModel.append(new AntenaBoyModel(this));
    mAntenaBoyModel.append(new AntenaBoyModel(this));
    mAntenaBoyModel.append(new AntenaBoyModel(this));

    QVariantList vl;
    for (int i = 0; i < mAntenaBoyModel.count(); ++i)
    {
        vl.append(QVariant::fromValue(mAntenaBoyModel.at(i)));
    }
    set_antenaBoyList(vl);
}

#include <QDebug>
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

void CharactersLogic::setMapModel(MapModel* mapModel_)
{
    mapModel = mapModel_;
}

bool CharactersLogic::tryToMove(int posX, int posY, int boySize)
{
    if (mapModel->getTileType(posX, posY) != TileType::Street) return false;
    if (mapModel->getTileType(posX + boySize, posY) != TileType::Street) return false;
    if (mapModel->getTileType(posX, posY + boySize) != TileType::Street) return false;
    if (mapModel->getTileType(posX + boySize, posY + boySize) != TileType::Street) return false;
    return true;
}

AntenaBoyModel* CharactersLogic::getAntenaBoySelected() {
    return mAntenaBoyModel.at(antenaBoySelected);
}

float SPEED = 2;

#include <QDebug>
void CharactersLogic::move() {
    int cnt = 1;
    for (AntenaBoyModel* antenaBoy : mAntenaBoyModel) {
        if (antenaBoy->moveX == 0 && antenaBoy->moveY == 0) continue;

        float newX = antenaBoy->posX() + SPEED * antenaBoy->moveX;
        if (newX < 0) newX = 0;

        float newY = antenaBoy->posY() + SPEED * antenaBoy->moveY;
        if (newY < 0) newY = 0;

        if (!tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX(); // jesli sie nie da sprobuj sie roszyc tylko w pionie
        }

        if (!tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX() + SPEED * antenaBoy->moveX;
            if (newX < 0) newX = 0;
            newY = antenaBoy->posY(); // jesli sie nie da sprobuj sie roszyc tylko w pionie
        }

        if (!tryToMove(newX, newY, antenaBoy->boySize())) {
            continue; // jesli sie nie da no to chu...
        }

        antenaBoy->set_posX(newX);
        antenaBoy->set_posY(newY);
    }
}


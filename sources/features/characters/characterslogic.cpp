#include "characterslogic.h"

CharactersLogic::CharactersLogic(QObject* parent)
    : QObject(parent)
{
    mAntenaBoyList.append(new AntenaBoyModel(0, 60, this));
    mAntenaBoyList.append(new AntenaBoyModel(1, 60, this));
    mAntenaBoyList.append(new AntenaBoyModel(2, 60, this));

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

void CharactersLogic::setMapModel(MapModel* mapModel_)
{
    mapModel = mapModel_;
}

AntenaBoyModel* CharactersLogic::getAntenaBoySelected() {
    return mAntenaBoyList.at(antenaBoySelected);
}

float SPEED = 2;

void CharactersLogic::move() {
    for (AntenaBoyModel* antenaBoy : mAntenaBoyList) {
        if (antenaBoy->moveX == 0 && antenaBoy->moveY == 0) continue;

        float newX = antenaBoy->posX() + SPEED * antenaBoy->moveX;
        if (newX < 0) newX = 0;

        float newY = antenaBoy->posY() + SPEED * antenaBoy->moveY;
        if (newY < 0) newY = 0;

        if (!mapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX(); // jesli sie nie da sprobuj sie ruszyc tylko w pionie
        }

        if (!mapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX() + SPEED * antenaBoy->moveX;
            if (newX < 0) newX = 0;
            newY = antenaBoy->posY(); // jesli sie nie da sprobuj sie ruszyc tylko w poziomie
        }

        if (!mapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            continue; // jesli sie nie da no to chu...
        }

        antenaBoy->set_posX(newX);
        antenaBoy->set_posY(newY);
    }
}


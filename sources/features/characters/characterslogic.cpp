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

    selectAntenaBoy(0);
}

void CharactersLogic::changSelectedAntenaBoy(int keyPressed)
{
    getAntenaBoySelected()->moveKeyReleased(Qt::Key_Up); // haczorek
    getAntenaBoySelected()->moveKeyReleased(Qt::Key_Left);

    getAntenaBoySelected()->set_isSelected(false);

    int selectedId = -1;
    if (keyPressed == Qt::Key_1) selectedId = 0;
    if (keyPressed == Qt::Key_2) selectedId = 1;
    if (keyPressed == Qt::Key_3) selectedId = 2;

    selectAntenaBoy(selectedId);
}

void CharactersLogic::selectAntenaBoy(int id)
{
    antenaBoySelected = id;
    getAntenaBoySelected()->set_isSelected(true);
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
    boy->makeInactiveForTime();
    boy->set_moveX(0);
    boy->set_moveY(0);
    setBoyToStartPosition(boy);
}

void CharactersLogic::restartPositionsAllAntenaBoys()
{
    for (int i = 0; i < mAntenaBoyList.count(); ++i)
    {
        setBoyToStartPosition(mAntenaBoyList.at(i));
        mAntenaBoyList.at(i)->set_isInactive(false);
        mAntenaBoyList.at(i)->range()->set_isInactive(false);
    }
}

void CharactersLogic::onJailOpend()
{
    for (int i = 0; i < mAntenaBoyList.count(); ++i)
    {
       mAntenaBoyList.at(i)->set_isInactive(false);
       mAntenaBoyList.at(i)->range()->set_isInactive(false);
    }
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
        if (antenaBoy->isInactive()) continue;

        if (antenaBoy->moveX() == 0 && antenaBoy->moveY() == 0) continue;

        float newX = antenaBoy->posX() + ANTENA_BOY_SPEED * antenaBoy->moveX();
        if (newX < 0) newX = 0;

        float newY = antenaBoy->posY() + ANTENA_BOY_SPEED * antenaBoy->moveY();
        if (newY < 0) newY = 0;

        if (!mMapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX(); // jesli sie nie da sprobuj sie ruszyc tylko w pionie
        }

        if (!mMapModel->tryToMove(newX, newY, antenaBoy->boySize())) {
            newX = antenaBoy->posX() + ANTENA_BOY_SPEED * antenaBoy->moveX();
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


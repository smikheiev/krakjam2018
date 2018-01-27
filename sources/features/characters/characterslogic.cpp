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

AntenaBoyModel* CharactersLogic::getAntenaBoySelected() {
    return mAntenaBoyModel.at(antenaBoySelected);
}

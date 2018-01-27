#ifndef CHARACTERSLOGIC_H
#define CHARACTERSLOGIC_H

#include "../../macros.h"
#include "antenaboymodel.h"

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

private:
    int antenaBoySelected = 1;

    AntenaBoyModel* getAntenaBoySelected();

    QList<AntenaBoyModel*> mAntenaBoyModel;
};

#endif // CHARACTERSLOGIC_H

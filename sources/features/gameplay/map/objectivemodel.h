#ifndef OBJECTIVEMODEL_H
#define OBJECTIVEMODEL_H

#include <QObject>

#include "../../../macros.h"

class ObjectiveModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, range)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(bool, isTransmissionOnLine)

public:
    ObjectiveModel(QObject* parent);
};

#endif // OBJECTIVEMODEL_H

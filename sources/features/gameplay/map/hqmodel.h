#ifndef HQMODEL_H
#define HQMODEL_H

#include <QObject>

#include "../../../macros.h"

class HQModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, range)

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(bool, isTransitionOnLine)

public:
    HQModel(QObject* parent);


};

#endif // HQMODEL_H

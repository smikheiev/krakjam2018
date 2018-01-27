#ifndef ESBEKMODEL_H
#define ESBEKMODEL_H

#include <QObject>

#include "../../macros.h"
#include "range/rangemodel.h"

class EsbekModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(int, moveX)
    AUTO_Q_PROPERTY(int, moveY)

    AUTO_Q_PROPERTY_CONSTANT(int, killRadius)
    AUTO_Q_PROPERTY_CONSTANT(int, seenRadius)

public:
    explicit EsbekModel(QObject *parent = nullptr);
};

#endif // ESBEKMODEL_H

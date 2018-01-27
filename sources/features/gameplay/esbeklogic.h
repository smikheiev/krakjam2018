#ifndef ESBEKLOGIC_H
#define ESBEKLOGIC_H

#include <QObject>

#include "../../macros.h"
#include "esbekmodel.h"
#include "map/mapmodel.h"

class EsbekLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(EsbekModel*, esbekModel)

public:
    explicit EsbekLogic(MapModel* mapModel, QObject *parent = nullptr);
};

#endif // ESBEKLOGIC_H

#ifndef ESBEKMODEL_H
#define ESBEKMODEL_H

#include <QObject>

#include "../../macros.h"

class EsbekModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(qint64, row)
    AUTO_Q_PROPERTY(qint64, column)
    AUTO_Q_PROPERTY(qint64, moveX)
    AUTO_Q_PROPERTY(qint64, moveY)

public:
    explicit EsbekModel(QObject *parent = nullptr);
};

#endif // ESBEKMODEL_H

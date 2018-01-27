#ifndef ESBEKMODEL_H
#define ESBEKMODEL_H

#include <QObject>

#include "../../macros.h"

class EsbekModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(qint64, row)
    AUTO_Q_PROPERTY(qint64, column)

public:
    explicit EsbekModel(QObject *parent = nullptr);
};

#endif // ESBEKMODEL_H

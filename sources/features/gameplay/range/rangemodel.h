#ifndef RANGE_H
#define RANGE_H

#include <QObject>

#include "../../../macros.h"

class RangeModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(qreal, radius)
    AUTO_Q_PROPERTY(int, column)
    AUTO_Q_PROPERTY(int, row)

public:
    explicit RangeModel(QObject *parent = nullptr);
};

#endif // RANGE_H

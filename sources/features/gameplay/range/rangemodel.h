#ifndef RANGE_H
#define RANGE_H

#include <QObject>
#include <QString>

#include "../../../macros.h"

class RangeModel : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY(qreal, radius)
    AUTO_Q_PROPERTY(int, posX)
    AUTO_Q_PROPERTY(int, posY)
    AUTO_Q_PROPERTY(bool, isTransmitting)
    AUTO_Q_PROPERTY(QString, rangeColor)

public:
    explicit RangeModel(QObject *parent = nullptr);

    void setToRow(const int row);
    void setToColumn(const int column);
};

#endif // RANGE_H

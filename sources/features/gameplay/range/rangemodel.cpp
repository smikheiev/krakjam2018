#include "rangemodel.h"

RangeModel::RangeModel(QObject *parent)
    : QObject(parent)
    , m_radius(-1)
    , m_column(-1)
    , m_row(-1)
{
}

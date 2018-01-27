#include "rangemodel.h"
#include "../constants.h"

RangeModel::RangeModel(QObject *parent)
    : QObject(parent)
    , m_radius(-1)
    , m_posX(-1)
    , m_posY(-1)
{
}

void RangeModel::setToRow(const int row)
{
    int posY = row * TILE_SIZE;
    set_posY(posY);
}

void RangeModel::setToColumn(const int column)
{
    int posX = column * TILE_SIZE;
    set_posX(posX);
}

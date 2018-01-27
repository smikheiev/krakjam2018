#include "tilemodel.h"

TileModel::TileModel(QObject *parent)
    : QObject(parent)
    , m_posX(0)
    , m_posY(0)
    , m_tileType(TileType::None)
{
}

#include "tilemodel.h"

TileModel::TileModel(QObject *parent)
    : QObject(parent)
    , m_tileType(TileType::None)
{
}

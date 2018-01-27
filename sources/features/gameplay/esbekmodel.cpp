#include "esbekmodel.h"

EsbekModel::EsbekModel(int id, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_posX(0)
    , m_posY(0)
    , m_moveX(0)
    , m_moveY(0)
    , m_killRadius(60)
    , m_seenRadius(100)
{
}

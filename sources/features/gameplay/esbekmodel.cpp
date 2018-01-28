#include "esbekmodel.h"
#include "constants.h"

EsbekModel::EsbekModel(int id, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_posX(0)
    , m_posY(0)
    , m_moveX(0)
    , m_moveY(0)
    , m_killRadius(ESBEK_KILL_RADIUS)
    , m_seenRadius(140)
{
}

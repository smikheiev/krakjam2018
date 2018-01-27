#include "esbekmodel.h"

EsbekModel::EsbekModel(QObject* parent)
    : QObject(parent)
    , m_posX(0)
    , m_posY(0)
    , m_moveX(0)
    , m_moveY(0)
    , m_killRange(new RangeModel(this))
    , m_seenRange(new RangeModel(this))
{
    killRange()->set_radius(25);
    killRange()->set_rangeColor("red");
    seenRange()->set_radius(40);
    seenRange()->set_rangeColor("blue");
}

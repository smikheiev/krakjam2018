#include "hqmodel.h"

HQModel::HQModel(QObject* parent):
    QObject(parent)
  , m_range(15)
  , m_posX(0)
  , m_posY(0)
  , m_isTransitionOnLine(false)
{

}

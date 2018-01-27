#include "esbeklogic.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, QObject *parent)
    : QObject(parent)
    , m_esbekModel(new EsbekModel(this))
{
    qDebug() << "map model: " << mapModel->getTileByposition(1,1)->tileType();
}

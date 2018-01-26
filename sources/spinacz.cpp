#include "spinacz.h"
#include "qmltypesregistrator.h"

Spinacz::Spinacz(QObject *parent)
    : QObject(parent)
    , mFeaturesRoot(new FeaturesRoot(this))
{
    QmlTypesRegistrator::registerTypes();
}

FeaturesRoot *Spinacz::featuresRoot() const
{
    return mFeaturesRoot;
}

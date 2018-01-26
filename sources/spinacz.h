#ifndef SPINACZ_H
#define SPINACZ_H

#include <QObject>

#include "features/featuresroot.h"

class Spinacz : public QObject
{
    Q_OBJECT

public:
    explicit Spinacz(QObject *parent = nullptr);

    FeaturesRoot* featuresRoot() const;

private:
    FeaturesRoot* mFeaturesRoot;
};

#endif // SPINACZ_H

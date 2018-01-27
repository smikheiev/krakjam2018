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

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    FeaturesRoot* mFeaturesRoot;
};

#endif // SPINACZ_H

#ifndef FEATURESROOT_H
#define FEATURESROOT_H

#include <QObject>

#include "../macros.h"
#include "appState/appstatefeature.h"
#include "exitApp/exitappfeature.h"
#include "gameplay/gameplayfeature.h"

class FeaturesRoot : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(AppStateFeature*, appState)
    AUTO_Q_PROPERTY_CONSTANT(ExitAppFeature*, exitApp)
    AUTO_Q_PROPERTY_CONSTANT(GameplayFeature*, gameplay)

public:
    explicit FeaturesRoot(QObject *parent = nullptr);

private:
    void createFeatures();
    void connectFeatures();
};

#endif // FEATURESROOT_H

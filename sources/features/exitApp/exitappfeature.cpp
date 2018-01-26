#include <QCoreApplication>

#include "exitappfeature.h"

ExitAppFeature::ExitAppFeature(QObject *parent)
    : QObject(parent)
{   
}

void ExitAppFeature::onAppStateChanged(const AppState appState)
{
    if (appState == AppState::Quit)
    {
        QCoreApplication::quit();
    }
}

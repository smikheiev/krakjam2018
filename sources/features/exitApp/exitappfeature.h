#ifndef EXITAPPFEATURE_H
#define EXITAPPFEATURE_H

#include <QObject>

#include "../appState/appstate.h"

class ExitAppFeature : public QObject
{
    Q_OBJECT

public:
    explicit ExitAppFeature(QObject *parent = nullptr);

public slots:
    void onAppStateChanged(const AppState appState);
};

#endif // EXITAPPFEATURE_H

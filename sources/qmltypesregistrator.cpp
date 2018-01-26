#include <QQmlEngine>

#include "qmltypesregistrator.h"
#include "features/appState/appstate.h"
#include "features/gameplay/gameplaystate.h"

void QmlTypesRegistrator::registerTypes()
{
    qmlRegisterUncreatableType<AppStateEnumWrapper>("Enums", 1, 0, "AppState", "Cannot create AppState in QML");
    qRegisterMetaType<AppState>("AppState");

    qmlRegisterUncreatableType<GameplayStateEnumWrapper>("Enums", 1, 0, "GameplayState", "Cannot create GameplayState in QML");
    qRegisterMetaType<GameplayState>("GameplayState");
}

#include <QQmlEngine>

#include "qmltypesregistrator.h"
#include "features/appState/appstate.h"
#include "features/gameplay/gameplaystate.h"
#include "features/gameplay/map/tiletype.h"
#include "features/gameplay/map/tilemodel.h"
#include "features/gameplay/map/objectivemodel.h"

void QmlTypesRegistrator::registerTypes()
{
    qmlRegisterUncreatableType<AppStateEnumWrapper>("Enums", 1, 0, "AppState", "Cannot create AppState in QML");
    qRegisterMetaType<AppState>("AppState");

    qmlRegisterUncreatableType<GameplayStateEnumWrapper>("Enums", 1, 0, "GameplayState", "Cannot create GameplayState in QML");
    qRegisterMetaType<GameplayState>("GameplayState");

    qmlRegisterUncreatableType<TileTypeEnumWrapper>("Enums", 1, 0, "TileType", "Cannot create TileType in QML");
    qRegisterMetaType<TileType>("TileType");

    qmlRegisterUncreatableType<AppStateEnumWrapper>("Enums", 1, 0, "OBJ_TYPE", "Cannot create AppState in QML");
    qRegisterMetaType<ObjectiveModel::OBJ_TYPE>("OBJ_TYPE");

    qRegisterMetaType<TileModel*>("TileModel*");
}

#include <QQmlEngine>

#include "qmltypesregistrator.h"
#include "features/appState/appstate.h"
#include "features/gameplay/gameplaystate.h"
#include "features/gameplay/map/tiletype.h"
#include "features/gameplay/map/tilemodel.h"
#include "features/sounds/soundtype.h"

void QmlTypesRegistrator::registerTypes()
{
    qmlRegisterUncreatableType<AppStateEnumWrapper>("Enums", 1, 0, "AppState", "Cannot create AppState in QML");
    qRegisterMetaType<AppState>("AppState");

    qmlRegisterUncreatableType<GameplayStateEnumWrapper>("Enums", 1, 0, "GameplayState", "Cannot create GameplayState in QML");
    qRegisterMetaType<GameplayState>("GameplayState");

    qmlRegisterUncreatableType<TileTypeEnumWrapper>("Enums", 1, 0, "TileType", "Cannot create TileType in QML");
    qRegisterMetaType<TileType>("TileType");

    qmlRegisterUncreatableType<SoundTypeEnumWrapper>("Enums", 1, 0, "SoundType", "Cannot create SoundType in QML");
    qRegisterMetaType<SoundType>("SoundType");

    qRegisterMetaType<TileModel*>("TileModel*");
}

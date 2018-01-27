import QtQuick 2.10

import "map/MapConstants.js" as MapConstants

Rectangle {
    id: esbek
    readonly property QtObject esbekModel: features.gameplay.esbekLogic.esbekModel

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    x: mapXStart + esbekModel.row * width
    y: mapYStart + esbekModel.column * width

    radius: width * 0.5

    property int moveDuration: 300
    property int mapXStart
    property int mapYStart

    Behavior on x {
        NumberAnimation { duration: moveDuration }
    }

    Behavior on y {
        NumberAnimation { duration: moveDuration }
    }
}

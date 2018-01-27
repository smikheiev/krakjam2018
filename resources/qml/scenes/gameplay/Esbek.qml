import QtQuick 2.10

import "map/MapConstants.js" as MapConstants
import "range"

Rectangle {
    id: esbek

    readonly property QtObject esbekModel: features.gameplay.esbekLogic.esbekModel

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    x: mapXStart + esbekModel.posX
    y: mapYStart + esbekModel.posY

    radius: width * 0.5

    property int moveDuration: 300
    property int mapXStart
    property int mapYStart

    Range {
        id: seenRange

        model: esbekModel.seenRange
    }

    Range {
        id: killRange

        model: esbekModel.killRange
    }
}

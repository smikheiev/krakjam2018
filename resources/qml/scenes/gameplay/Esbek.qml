import QtQuick 2.10

import "map/MapConstants.js" as MapConstants
import "range"

Item {
    id: esbek

    readonly property QtObject esbekModel: features.gameplay.esbekLogic.esbekModel

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    x: esbekModel.posX
    y: esbekModel.posY

    Rectangle {
        width: MapConstants.TILE_SIZE * 0.75
        height: MapConstants.TILE_SIZE * 0.75
        anchors {
            centerIn: parent
        }

        radius: width * 0.5
        color: "pink"
    }

    RangeCircle {
        id: seenRangeCircle

        anchors {
            centerIn: parent
        }

        size: esbekModel.seenRadius
        borderColor: "yellow"
        sonarDelay: 0
    }

    RangeCircle {
        id: killRangeCircle

        anchors {
            centerIn: parent
        }

        size: esbekModel.killRadius
        borderColor: "red"
        sonarDelay: 0
    }
}

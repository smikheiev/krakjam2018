import QtQuick 2.10

import "map/MapConstants.js" as MapConstants
import "range"

Item {
    id: esbek

    property QtObject esbekModel

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    x: esbekModel.posX
    y: esbekModel.posY

    Image {
        source: "qrc:/images/map/SBK_probka1.png"

        anchors {
            centerIn: parent
        }
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

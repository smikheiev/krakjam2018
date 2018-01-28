import QtQuick 2.10

import "map/MapConstants.js" as MapConstants
import "range"

Item {
    id: esbek

    property QtObject esbekModel

    readonly property int moveX: esbekModel ? esbekModel.moveX : 0
    property bool flipImage: false

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    x: esbekModel.posX
    y: esbekModel.posY

    onMoveXChanged: {
        if (moveX != 0) {
            flipImage = moveX == 1
        }
    }

    Image {
        id: image
        anchors {
            centerIn: parent
        }

        transform:
            Rotation {
            origin.x: image.width/2;
            origin.y: image.height/2;
            axis.x:0; axis.y:1; axis.z:0
            angle: flipImage ? 180 : 0
        }

        source: getAntenaBoyImage()
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

    function getAntenaBoyImage() {
        var a = 70 // do manipulowania szybkoscia przebierania nozkami :)
        var modulo = 1 + (esbekModel.posX + esbekModel.posY) % a
        var img_nr = 1
        if (modulo < a/3) {
            img_nr = 2
        } else if (modulo < (2*a/3)) {
            img_nr = 3
        }

        return "qrc:/images/map/SBK_" + img_nr + ".png"
    }
}

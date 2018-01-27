import QtQuick 2.10

import "map/MapConstants.js" as MapConstants

Rectangle {
    id: esbek

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    radius: width * 0.5

    property int moveDuration: 500
    property int mapXStart
    property int mapXEnd
    property int mapYStart
    property int mapYEnd

    property bool movePositive: true

    property bool isVerticalMove

    Behavior on x {
        NumberAnimation { duration: moveDuration }
    }

    Behavior on y {
        NumberAnimation { duration: moveDuration }
    }

    Timer {
        running: parent.visible && isVerticalMove
        interval: moveDuration
        repeat: true

        onTriggered: {
            if (y <= mapYStart) {
                movePositive = true
            }
            if (y + height >= mapYEnd ) {
                movePositive = false
            }

            y = movePositive ? y + height : y - height
        }
    }

    Timer {
        running: parent.visible && !isVerticalMove
        interval: moveDuration
        repeat: true

        onTriggered: {
            if (x <= mapXStart) {
                movePositive = true
            }
            if (x + width >= mapXEnd ) {
                movePositive = false
            }

            x = movePositive ? x + width : x - width
        }
    }

}

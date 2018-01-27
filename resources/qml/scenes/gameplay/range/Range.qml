import QtQuick 2.10

import "../map/MapConstants.js" as MapConstants

Item {
    id: range

    property QtObject model: null

    QtObject {
        id: priv

        readonly property bool hasRange: model
        readonly property double radius: model ? model.radius : 0.0
        readonly property int posX: model ? model.posX : 0
        readonly property int posY: model ? model.posY : 0
    }

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE
    x: priv.posX
    y: priv.posY

    visible: priv.hasRange

    SequentialAnimation {
        loops: Animation.Infinite
        running: priv.hasRange

        NumberAnimation { target: range; property: "opacity"; duration: 1500; from: 1; to: 0 }
        NumberAnimation { target: range; property: "opacity"; duration: 1500; from: 0; to: 1 }
    }

    Rectangle {
        id: rangeCircle

        width: priv.radius * 2
        height: width
        anchors {
            centerIn: parent
        }

        radius: width / 2
        color: "transparent"
        border {
            color: model ? model.rangeColor : "cyan"
            width: rangeCircle.width * 0.3
        }
    }
}

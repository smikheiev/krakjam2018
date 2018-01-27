import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../range"

Item {
    id: antenaBoy

    property QtObject antenaBoyModel
    property bool isTransmitting: antenaBoyModel ? antenaBoyModel.range.isTransmitting : false
    property bool isInactive: antenaBoyModel ? antenaBoyModel.isInactive : false
    property int posX: antenaBoyModel ? antenaBoyModel.posX : 0
    property int posY: antenaBoyModel ? antenaBoyModel.posY : 0

    width: antenaBoyModel.boySize
    height: antenaBoyModel.boySize

    x: posX
    y: posY

    onIsInactiveChanged: {
        if (!isInactive) {
            antenaBoy.opacity = 1
        }
    }

    Image {
        anchors {
            centerIn: parent
        }

        source: "qrc:/images/map/AntenaBoy_DoPoprawki.png"
    }

    SequentialAnimation {
        id: inactiveAnimation

        running: isInactive
        loops: Animation.Infinite

        NumberAnimation { target: antenaBoy; property: "opacity"; duration: 250; from: 1; to: 0 }
        NumberAnimation { target: antenaBoy; property: "opacity"; duration: 250; from: 0; to: 1 }
    }

    Text {
        anchors {
            centerIn: parent
        }

        text: (antenaBoyModel.id + 1)
        font {
            bold: true
            pixelSize: 28
        }
        color: "white"
    }
}

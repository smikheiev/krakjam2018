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
    property int moveX: antenaBoyModel ? antenaBoyModel.moveX : 0
    property bool flipImage: false

    width: antenaBoyModel.boySize
    height: antenaBoyModel.boySize

    x: posX
    y: posY

    onMoveXChanged: {
        if (moveX != 0) {
            flipImage = moveX == 1
        }
    }

    onIsInactiveChanged: {
        if (!isInactive) {
            antenaBoy.opacity = 1
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

    function getAntenaBoyImage() {
        var a = 50 // do manipulowania szybkoscia przebierania nozkami :)
        var modulo = 1 + (posX + posY) % a
        var img_nr = modulo > (a/2) - 1 ? 0 : 1
        return "qrc:/images/map/AntenaBoy_" + img_nr + ".png"
    }
}

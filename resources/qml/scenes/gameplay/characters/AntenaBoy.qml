import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../range"

Rectangle {
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
    color: isInactive ? "black" : (isTransmitting ? "#900" : "white")

    Text {
        anchors {
            centerIn: parent
        }

        text: (antenaBoyModel.id + 1)
        font {
            bold: true
            pixelSize: 14
        }
    }
}

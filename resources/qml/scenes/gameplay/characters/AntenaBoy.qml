import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../range"

Rectangle {
    id: antenaBoy

    property QtObject antenaBoyModel

    width: antenaBoyModel.boySize
    height: antenaBoyModel.boySize

    x: antenaBoyModel ? antenaBoyModel.posX : 0
    y: antenaBoyModel ? antenaBoyModel.posY : 0

    color: "white"

    Range {
        id: range

        anchors {
            centerIn: parent
        }

        model: antenaBoyModel.range
    }
}

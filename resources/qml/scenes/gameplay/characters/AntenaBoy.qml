import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: antenaBoy

    property QtObject antenaBoyModel

    width: antenaBoyModel.boySize
    height: antenaBoyModel.boySize

    x: antenaBoyModel ? antenaBoyModel.posX : 0
    y: antenaBoyModel ? antenaBoyModel.posY : 0

    color: "white"
}

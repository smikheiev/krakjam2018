import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: antenaBoy

    property QtObject antenaBoyModel

    width: 30
    height: 30

    x: antenaBoyModel ? antenaBoyModel.posX : 0
    y: antenaBoyModel ? antenaBoyModel.posY : 0

    color: "green"

    Timer {
        id: moveTimer

        running: true
        repeat: true
        interval: 15

        onTriggered: {
            antenaBoyModel.move()
        }
    }
}

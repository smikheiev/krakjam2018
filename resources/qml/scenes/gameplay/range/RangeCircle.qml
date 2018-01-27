import QtQuick 2.10

Rectangle {
    id: rangeCircle

    property int size
    property color borderColor
    property int sonarDelay
    property bool isTransmitting

    QtObject {
        id: priv

        readonly property int animationDuration: 2500
        property bool animateSonar: false
    }

    width: size
    height: size
    radius: size / 2
    color: "transparent"
    visible: priv.animateSonar

    border {
        color: borderColor
        width: 4
    }

    ParallelAnimation {
        running: priv.animateSonar
        loops: Animation.Infinite
        NumberAnimation { target: rangeCircle; property: "scale"; duration: priv.animationDuration; from: 0; to: 1 }
        NumberAnimation { target: rangeCircle; property: "opacity"; duration: priv.animationDuration; from: 1; to: 0.2 }
    }

    Timer {
        id: sonarTimer

        interval: sonarDelay
        repeat: false
        running: true

        onTriggered: {
            priv.animateSonar = true
        }
    }
}

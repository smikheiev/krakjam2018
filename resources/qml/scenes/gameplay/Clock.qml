import QtQuick 2.10

Image {
    id: clock

    width: sourceSize.width
    height: sourceSize.height

    source: "qrc:/images/ui/clock_bg.png"

    Image {
        id: clockLine

        width: sourceSize.width
        height: sourceSize.height

        anchors {
            horizontalCenter: clock.horizontalCenter
        }

        source: "qrc:/images/ui/clock_line.png"
    }

    SequentialAnimation {
        id: bounceAnimation

        running: parent.visible

        loops: Animation.Infinite

        NumberAnimation { target: clock; property: "scale"; from: 1.0; to: 1.15; duration: 400 }
        PauseAnimation { duration:  200 }
        NumberAnimation { target: clock; property: "scale"; from: 1.15; to: 1.0; duration: 400 }
        PauseAnimation { duration:  200 }
    }
}

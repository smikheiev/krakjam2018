import QtQuick 2.10

Image {
    id: clock

    width: sourceSize.width
    height: sourceSize.height

    property int timeToEnd: features.gameplay.scoreLogic.lifeTime
    property bool isFinishTime: timeToEnd < 10000

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

        running: parent.visible && !isFinishTime

        loops: Animation.Infinite

        NumberAnimation { target: clock; property: "scale"; from: 1.0; to: 1.15; duration: 400 }
        PauseAnimation { duration:  200 }
        NumberAnimation { target: clock; property: "scale"; from: 1.15; to: 1.0; duration: 400 }
        PauseAnimation { duration:  200 }
    }

    SequentialAnimation {
        id: bounceAnimationFaster

        running: parent.visible && isFinishTime

        loops: Animation.Infinite

        NumberAnimation { target: clock; property: "scale"; from: 1.0; to: 1.2; duration: 200 }
        PauseAnimation { duration:  100 }
        NumberAnimation { target: clock; property: "scale"; from: 1.2; to: 1.0; duration: 200 }
        PauseAnimation { duration:  100 }
    }
}

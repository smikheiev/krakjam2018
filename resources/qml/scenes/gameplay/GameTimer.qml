import QtQuick 2.10

Item {
    id: gameTimer

    property QtObject scoreLogic: features.gameplay.scoreLogic

    property int borderSize: 2
    property int progressBarWidth: width - 2 * borderSize
    property bool isPauseMode: false

    property bool isReady: false

    signal roundFailed()

    width: progressBarFrame.width
    height: progressBarFrame.height

    Rectangle {
        color: "#FF1C1E15"

        width: progressBar.width - 60
        height: progressBar.height
        x: 30

        anchors {
            verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        width : progressBar.width * (scoreLogic.lifeTime / scoreLogic.MAX_LIFE_TIME) - 60
        height: progressBar.height
        x: 30

        anchors {
            verticalCenter: parent.verticalCenter
        }

        color: "black"

        clip: true

        Image {
            id: progressBar

            width: sourceSize.width
            height: sourceSize.height

            source: "qrc:/images/ui/time_yellow.png"
            fillMode: Image.PreserveAspectCrop
        }
    }


    Image {
        id: progressBarFrame
        width: sourceSize.width
        height: sourceSize.height

        source: "qrc:/images/ui/time_frame.png"
    }

    Timer {
        id: lifeTimeTimer

        interval: 15
        repeat: true
        running: isReady

        onTriggered: {
            if (scoreLogic.lifeTime > 0) {
                scoreLogic.lifeTime -= interval
            } else {
                roundFailed()
            }
        }
    }

    Clock {
        anchors {
            right: parent.left
            rightMargin: -50
        }
    }
}

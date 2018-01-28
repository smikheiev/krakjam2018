import QtQuick 2.10

Rectangle {
    id: gameTimer

    property QtObject scoreLogic: features.gameplay.scoreLogic

    property int borderSize: 2
    property int progressBarWidth: width - 2 * borderSize
    property bool isPauseMode: false

    property bool isReady: false

    signal roundFailed()

    color: "black"

    border.color: "white"
    border.width: borderSize

    Rectangle {
        id: progressBar

        x: borderSize
        y: borderSize
        width: parent.width * (scoreLogic.lifeTime / scoreLogic.MAX_LIFE_TIME)
        height: parent.height

        color: "#26FF00"
    }

    Text {
        id: scoreText

        anchors {
            left: parent.left
            leftMargin: 30
            top: parent.top
            topMargin: 20
        }

        text: "Score: " + scoreLogic.score
        color: "red"
    }

    Text {

        anchors {
            left: parent.left
            leftMargin: 30
            top: scoreText.bottom
        }

        text: "Misions Completed: " + scoreLogic.missionsCompleted
        color: "red"
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
}

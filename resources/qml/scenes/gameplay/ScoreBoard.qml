import QtQuick 2.10

Image {
    id: scoreBoard

    width: sourceSize.width
    height: sourceSize.height

    source: "qrc:/images/ui/score_board.png"

    Text {
        id: scoreText

        anchors {
            top: parent.top
            topMargin: 40
            left: parent.left
            leftMargin: 32
        }

        text: "SCORE: " + features.gameplay.scoreLogic.score
        font.bold: true
        font.pixelSize: 20
        color: "#FBB03B"

        rotation: -5
    }

    Text {
        id: missionText

        anchors {
            top: scoreText.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 32
        }

        text: "MISSIONS: " + features.gameplay.scoreLogic.missionsCompleted
        font.bold: true
        font.pixelSize: 20
        color: "#FBB03B"

        rotation: -5
    }
}

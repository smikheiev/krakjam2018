import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../"
import "./gameEndPopup"
import "../../common"
import "./map"
import "./UI"

BaseScene {
    id: gameplayScene

    sceneAppState: AppState.Gameplay

    Map {
        id: map

        anchors {
            fill: parent
        }
    }

    GameTimer {
        id: gameTimer

        y: -25
        scale: 0.6

        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: 20
        }

        onRoundFailed: {
            features.gameplay.roundFailed()
            roundLosePopup.visible = true
        }
    }

    Text {
        id: scoreText

        anchors {
            left: parent.left
            leftMargin: 30
            top: parent.top
            topMargin: 20
        }

        text: "Score: " + features.gameplay.scoreLogic.score
        color: "red"
    }

    Text {
        id: missionText

        anchors {
            left: parent.left
            leftMargin: 30
            top: scoreText.bottom
        }

        text: "Misions Completed: " + features.gameplay.scoreLogic.missionsCompleted
        color: "red"
    }

    BottomPanel {
        id: bottomPanel

        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }

    WonPopup {
        id: wonPopup

        width: parent.width
        height: parent.height
    }

    LosePopup {
        id: losePopup

        width: parent.width
        height: parent.height
    }

    RoundWonPopup {
        id: roundWonPopup

        visible: false

        anchors {
            centerIn: parent
        }
    }

    RoundLosePopup {
        id: roundLosePopup

        visible: false

        anchors {
            centerIn: parent
        }
    }

    Connections {
        target: features.gameplay

        onRestartTimerNeeded: {
            gameTimer.isReady = true
        }
    }
}

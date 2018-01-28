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

        height: 50
        width: 1000
        anchors {
            horizontalCenter: parent.horizontalCenter
        }

        onRoundFailed: {
            features.gameplay.roundFailed()
            roundLosePopup.visible = true
        }
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

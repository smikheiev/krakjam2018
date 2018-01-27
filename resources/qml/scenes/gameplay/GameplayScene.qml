import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../"
import "./gameEndPopup"
import "../../common"
import "./map"

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

        height: 18
        width: map.gridMapWidth
        x: map.mapGridPosX
        y: map.mapGridPosY - (height + 8)

        onRoundFailed: {
            features.gameplay.roundFailed()
            roundLosePopup.visible = true
        }

        Component.onCompleted: {
            gameTimer.startTimer()
        }
    }

    Item {
        id: charactersContainer

        x: map.mapGridPosX
        y: map.mapGridPosY

        Repeater {
            model: features.gameplay.charactersLogic.antenaBoyList

            AntenaBoy {
                antenaBoyModel: modelData
            }
        }

        Timer {
            id: moveTimer

            running: true
            repeat: true
            interval: 15

            onTriggered: {
                features.gameplay.charactersLogic.move()
                features.gameplay.transmissionLogic.checkTransmission()
                features.gameplay.esbekLogic.moveEsbek()
            }
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

        onObjectiveCompleted: {
            gameTimer.pauseTimer()
            roundWonPopup.visible = true
        }

        onRestartTimerNeeded: {
            gameTimer.startTimer()
        }
    }
}

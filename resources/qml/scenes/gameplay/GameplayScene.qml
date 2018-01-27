import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../"
import "./gameEndPopup"
import "../../common"
import "./characters"
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
}

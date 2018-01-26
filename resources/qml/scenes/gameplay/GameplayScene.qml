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

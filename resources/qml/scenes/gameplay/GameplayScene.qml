import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../"
import "./gameEndPopup"
import "../../common"

BaseScene {
    id: gameplayScene

    sceneAppState: AppState.Gameplay

    Rectangle {
        anchors {
            fill: parent
        }
        color: "blue"
    }

    Column {
        id: buttondColumn

        anchors {
            centerIn: parent
        }

        spacing: 20

        ButtonWithText {
            id: winButton

            textString: "Win"

            onClicked: {
                features.gameplay.tryChangeStateTo(GameplayState.Won)
            }
        }

        ButtonWithText {
            id: looseButton

            textString: "Loose"

            onClicked: {
                features.gameplay.tryChangeStateTo(GameplayState.Lose)
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

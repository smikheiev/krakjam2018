import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../common"

BaseScene {
    id: menuScene

    sceneAppState: AppState.Menu

    Rectangle {
        anchors {
            fill: parent
        }
        color: "red"
    }

    Column {
        id: buttondColumn

        anchors {
            centerIn: parent
        }

        spacing: 20

        ButtonWithText {
            id: playButton

            textString: "Play"

            onClicked: {
                features.appState.tryChangeStateTo(AppState.Gameplay)
            }
        }

        ButtonWithText {
            id: exitButton

            textString: "Exit"

            onClicked: {
                features.appState.tryChangeStateTo(AppState.Quit)
            }
        }
    }
}

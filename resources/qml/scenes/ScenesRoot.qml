import QtQuick 2.10

import Enums 1.0

import "./gameplay"

Item {
    id: rootScene

    LoadingScene {
        id: loadingScene

        anchors {
            fill: parent
        }
    }

    MenuScene {
        id: menuScene

        anchors {
            fill: parent
        }
    }

    GameplayScene {
        id: gameplayScene

        anchors {
            fill: parent
        }
    }

    Component.onCompleted: {
        features.appState.tryChangeStateTo(AppState.Gameplay)
    }
}

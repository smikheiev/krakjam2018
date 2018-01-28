import QtQuick 2.10
import QtQuick.Controls 2.3

import Enums 1.0

import "../common"

BaseScene {
    id: menuScene

    sceneAppState: AppState.Menu

    Image {
        id: bg
        anchors.fill: parent

        source: "qrc:/images/menu.png"
    }

    Button {
        id: button

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 50
        }

        text: "START"
        font.pixelSize: 80
        font.bold: true

        background: Rectangle {
            anchors {
                fill: parent
            }

            radius: 6

            color: button.pressed ? "#dd9c33" : "#FBB03B"
        }

        onClicked: {
            features.appState.tryChangeStateTo(AppState.Gameplay)
        }
    }
}

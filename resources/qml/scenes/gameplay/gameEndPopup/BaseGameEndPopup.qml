import QtQuick 2.10
import QtQuick.Controls 2.2

import Enums 1.0

import "../../../common"

Popup {
    id: baseGameEndPopup

    property int popupGameplayState: -1
    property string imageSource: ""

    margins: 0
    padding: 0

    Rectangle {
        id: background

        anchors {
            fill: parent
        }

        color: "black"
        opacity: 0.7
    }

    Image {
        id: image

        anchors {
            centerIn: parent
        }

        source: imageSource
    }

    ButtonWithText {
        id: goToMenuButton

        width: 200
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: image.bottom
        }

        textString: "Back to menu"

        onClicked: {
            features.gameplay.tryChangeStateTo(GameplayState.None)
        }
    }

    Connections {
        target: features.gameplay
        onCurrentGameplayStateChanged: {
            if (features.gameplay.currentGameplayState.valueOf() === popupGameplayState) {
                open()
            }
            else {
                close()
            }
        }
    }
}

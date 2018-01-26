import QtQuick 2.10

import Enums 1.0

BaseScene {
    id: loadingScene

    property int loadingTimeMs: 3000
    property int maxLoadingPoints: 3

    sceneAppState: AppState.Loading

    onSceneShown: {
        priv.isLoading = true
    }

    onSceneHided: {
        priv.isLoading = false
        priv.loadingPoints = ""
    }

    QtObject {
        id: priv

        property bool isLoading: false
        property string loadingPoints: ""
    }

    Rectangle {
        anchors {
            fill: parent
        }
        color: "blue"

        ColorAnimation on color{
            from: "blue"
            to: "yellow"
            duration: loadingTimeMs * 0.75
            running: priv.isLoading
        }
    }

    Text {
        id: loadingText
        anchors {
            centerIn: parent
        }

        text: qsTr("Loading")

        font {
            family: fonts.trebuchet
            pointSize: 44
        }
    }

    Text {
        id: loadingTextPoints

        anchors {
            verticalCenter: loadingText.verticalCenter
            left: loadingText.right
        }

        text: priv.loadingPoints

        font: loadingText.font
    }

    Timer {
        id: loadingPointsTimer

        interval: 250
        running: priv.isLoading
        repeat: true

        onTriggered: {
            if (priv.loadingPoints.length === maxLoadingPoints) {
                priv.loadingPoints = ""
            } else {
                priv.loadingPoints += "."
            }
        }
    }

    Timer {
        id: loadingCompleteTimer

        interval: loadingTimeMs
        running: priv.isLoading

        onTriggered: {
            features.appState.tryChangeStateTo(AppState.Menu)
        }
    }
}

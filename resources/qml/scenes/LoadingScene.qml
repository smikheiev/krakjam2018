import QtQuick 2.10

import Enums 1.0

BaseScene {
    id: loadingScene

    property int loadingTimeMs: 5000
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

    Image {
        id: splashBg

        anchors.fill: parent

        source: "qrc:/images/Splash_3.png"
    }

    Image {
        id: splash1

        width: parent.width
        height: parent.height

        source: "qrc:/images/Splash_2.png"

        NumberAnimation on y {
            from: 100;
            to: 0;
            duration: 1000
        }
    }

    Image {
        width: parent.width
        height: parent.height

        x: -parent.width

        source: "qrc:/images/Splash_1.png"

        NumberAnimation on x {
            to: 0;
            duration: 1000;
            running: splash1.y === 0
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

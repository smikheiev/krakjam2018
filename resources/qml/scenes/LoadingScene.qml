import QtQuick 2.10

import Enums 1.0

BaseScene {
    id: loadingScene

    property int loadingTimeMs: 2000
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

    NumberAnimation on scale {
        from: 1.5;
        to: 1;
        duration: 500
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
    }

    Image {
        id: image11

        height: parent.height
        fillMode: Image.PreserveAspectFit

        x: 0 - 150

        source: "qrc:/images/Splash_1_1.png"

        NumberAnimation on x {
            to: 0;
            duration: 500;
        }
    }

    Image {
        id: image12

        height: parent.height
        fillMode: Image.PreserveAspectFit

        x: parent.width - image12.width + 200
        source: "qrc:/images/Splash_1_2.png"

        NumberAnimation on x {
            to: parent.width - image12.width;
            duration: 500;
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

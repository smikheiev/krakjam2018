import QtQuick 2.10

import Enums 1.0

Item {
    id: baseScene

    signal sceneShown
    signal sceneHided

    property int sceneAppState: AppState.None

    visible: false

    Connections {
        target: features.appState
        onCurrentAppStateChanged: {
            if (features.appState.currentAppState.valueOf() === sceneAppState) {
                baseScene.visible = true
                sceneShown()
            }
            else {
                baseScene.visible = false
                sceneHided()
            }
        }
    }
}

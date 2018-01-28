import QtQuick 2.10
import QtQuick.Window 2.10

import "./scenes"

Window {
    id: main

    visible: true
    width: 1920 * 0.65
    height: 1080 * 0.65
    title: qsTr("Hello World")

    Fonts {
        id: fonts
    }

    ScenesRoot {
        id: rootScene

        anchors {
            fill: parent
        }
    }

    SoundsPlayer {
        id: soundsPlayer
    }

    Connections {
        target: features
        onShowKoza: {
            kozaAnimation.start()
        }
    }

    Image {
        id: koza
        source: "qrc:/images/kozy-w-pizamach_24131765.png"

        x: offScreenX
        y: main.height - koza.height + 70

        scale: 0.7

        property int offScreenX: main.width
        property int onScreenX: main.width - koza.width + 100
    }

    SequentialAnimation {
        id: kozaAnimation

        NumberAnimation { target: koza; property: "x"; duration: 1000; from: koza.offScreenX; to: koza.onScreenX }
        PauseAnimation { duration: 500 }
        NumberAnimation { target: koza; property: "x"; duration: 1000; from: koza.onScreenX; to: koza.offScreenX }
    }
}

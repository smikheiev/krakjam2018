import QtQuick 2.10
import QtQuick.Window 2.10

import "./scenes"

Window {
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
}

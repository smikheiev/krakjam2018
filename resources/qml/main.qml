import QtQuick 2.10
import QtQuick.Window 2.10

import "./scenes"

Window {
    visible: true
    width: 640
    height: 480
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

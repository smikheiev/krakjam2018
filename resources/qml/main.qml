import QtQuick 2.10
import QtQuick.Window 2.10

import "./scenes"

Window {
    visible: true
    width: 1700
    height: 1000
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

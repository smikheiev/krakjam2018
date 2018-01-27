import QtQuick 2.10

import "../map/MapConstants.js" as MapConstants
import "../../../common/"

Item {
    id: objective

    property QtObject model

    property bool isTransmissionMode: model ? model.range.isTransmitting : false
    property int transmissionTime: model ? model.transmissionTime : 0
    property double progressValue
    property int temp: 0

    onIsTransmissionModeChanged: {
        if (isTransmissionMode) {
            animationProgress.restart()
        }
    }

    QtObject {
        id: priv

        readonly property int posX: model ? model.posX : 0
        readonly property int posY: model ? model.posY : 0
    }

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE
    x: priv.posX - width / 2
    y: priv.posY - height / 2

    Rectangle {
        anchors {
            fill: parent
        }
        color: "black"
    }

    Image {
        width: parent.width * 2
        height: parent.height * 2
        anchors {
            centerIn: parent
        }

        visible: isTransmissionMode
        source: "qrc:/images/happy.png"

        layer.enabled: true
        layer.effect: CircleProgressShader {
            progress: progressValue
            reachedProgressOpacity: 1.0
            unreachedProgressOpacity: 0.3
        }
    }

    NumberAnimation {
        id: animationProgress

        target: objective
        property: "progressValue"
        from: 0.0
        to: 1.0
        duration: transmissionTime
    }
}

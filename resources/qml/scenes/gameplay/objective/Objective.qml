import QtQuick 2.10

import "../map/MapConstants.js" as MapConstants
import "../../../common/"

Item {
    id: objective

    property QtObject model

    property int type: model ? model.type : 0
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
    x: priv.posX
    y: priv.posY

    Image {
        id: icon

        anchors {
            centerIn: parent
        }

        source: getIcon()
    }

    Image {
        width: parent.width
        height: parent.height
        anchors {
            centerIn: parent
        }

        visible: isTransmissionMode
        source: "qrc:/images/map/objective_timer.png"

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

    SequentialAnimation {
        id: bounceAnimation

        running: parent.visible

        loops: Animation.Infinite

        NumberAnimation { target: icon; property: "scale"; from: 1.0; to: 1.3; duration: 400 }
        PauseAnimation { duration:  200 }
        NumberAnimation { target: icon; property: "scale"; from: 1.3; to: 1.0; duration: 400 }
        PauseAnimation { duration:  200 }
    }

    function getIcon() {
        if (type == 0) {
            var index = Math.floor(Math.random() * 3)
            return "qrc:/images/map/objective_" + index + ".png"
        } else {
            return "qrc:/images/map/wiezienie.png"
        }
    }
}

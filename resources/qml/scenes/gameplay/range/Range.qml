import QtQuick 2.10

import "../map/MapConstants.js" as MapConstants

Item {
    id: range

    property QtObject model: null
    readonly property bool isTransmitting: model ? model.isTransmitting : false
    readonly property bool isInactive: model ? model.isInactive : false

    QtObject {
        id: priv

        readonly property bool hasRange: model
        readonly property double radius: model ? model.radius : 0.0
        readonly property int posX: model ? model.posX : 0
        readonly property int posY: model ? model.posY : 0
    }

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE
    x: priv.posX
    y: priv.posY

    visible: !isInactive

    Repeater {
        id: rangeCirclesRepeater

        model: 3

        delegate: RangeCircle {
            anchors {
                centerIn: parent
            }

            size: priv.radius * 2
            borderColor: range.isTransmitting ? "cyan" : "pink"
            sonarDelay: index * 500
        }
    }
}

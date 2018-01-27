import QtQuick 2.10

import "../map/MapConstants.js" as MapConstants

Item {
    id: objective

    property QtObject model

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
        color: "yellow"
    }
}

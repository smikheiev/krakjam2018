import QtQuick 2.10

import "./MapConstants.js" as MapConstants

Item {
    id: map

    readonly property QtObject mapModel: features.gameplay.mapModel

    Rectangle {
        id: background

        anchors {
            fill: parent
        }

        color: "black"
    }

    Grid {
        id: mapGrid

        anchors {
            centerIn: parent
        }
        columns: mapModel.width
        rows: mapModel.height
        spacing: 0

        Repeater {
            model: mapModel.width * mapModel.height

            delegate: Tile {
                width: MapConstants.TILE_SIZE
                height: MapConstants.TILE_SIZE

                tileIndex: index
            }
        }
    }
}

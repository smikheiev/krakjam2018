import QtQuick 2.10

import "./MapConstants.js" as MapConstants

import "../range"

Item {
    id: map

    readonly property QtObject mapModel: features.gameplay.mapModel
    readonly property var ranges: features.gameplay.ranges

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

    Item {
        id: rangesContainer

        x: mapGrid.x
        y: mapGrid.y

        Repeater {
            id: rangesRepeater

            model: ranges

            delegate: Range {
                model: display // display - standart Qt Role "Qt::DisplayRole"
            }
        }
    }
}

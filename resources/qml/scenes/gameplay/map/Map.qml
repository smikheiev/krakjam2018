import QtQuick 2.10

import "./MapConstants.js" as MapConstants
import "../"

import "../range"

Item {
    id: map

    readonly property QtObject mapModel: features.gameplay.mapModel
    readonly property var ranges: features.gameplay.ranges

    property int mapGridPosX: mapGrid.x
    property int mapGridPosY: mapGrid.y

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

    Esbek {
        id: esbek

        x: mapXStart
        y: mapYStart

        mapXStart: mapGrid.x
        mapXEnd: mapGrid.x + mapGrid.width
        mapYStart: mapGrid.y
        mapYEnd: mapGrid.y + mapGrid.height

        color: "#ff00ff"

        isVerticalMove: true

    }

    Esbek {
        id: esbek2

        x: mapXEnd - width
        y: mapYStart

        mapXStart: mapGrid.x
        mapXEnd: mapGrid.x + mapGrid.width
        mapYStart: mapGrid.y
        mapYEnd: mapGrid.y + mapGrid.height

        color: "#ffff00"

        isVerticalMove: false
    }


    Esbek {
        id: esbek3

        x: mapXStart
        y: mapYEnd - height

        mapXStart: mapGrid.x
        mapXEnd: mapGrid.x + mapGrid.width
        mapYStart: mapGrid.y
        mapYEnd: mapGrid.y + mapGrid.height

        color: "#00ffdf"

        isVerticalMove: false
    }
}

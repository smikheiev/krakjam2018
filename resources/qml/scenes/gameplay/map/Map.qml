import QtQuick 2.10

import "./MapConstants.js" as MapConstants
import "../"
import "../range"
import "../objective"

Item {
    id: map

    readonly property QtObject mapModel: features.gameplay.mapModel
    readonly property var ranges: features.gameplay.ranges
    readonly property var objectives: features.gameplay.objectiveLogic.objectives

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
        id: objectivesContainer

        x: mapGrid.x
        y: mapGrid.y

        Repeater {
            id: objectivesRepeater

            model: objectives

            delegate: Objective {
                model: display // display - standart Qt Role "Qt::DisplayRole"
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

    Item {
        id: esbeksContainer

        x: mapGrid.x
        y: mapGrid.y

        Esbek {
            id: esbek
        }
    }
}

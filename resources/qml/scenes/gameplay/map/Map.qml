import QtQuick 2.10

import "../"
import "../range"
import "../objective"
import "../characters"

Item {
    id: map

    readonly property QtObject mapModel: features.gameplay.mapModel
    readonly property var ranges: features.gameplay.ranges
    readonly property var objectives: features.gameplay.objectiveLogic.objectives

    scale: 0.65
    property int gridMapWidth: mapGrid.width

    property int mapGridPosX: mapGrid.x
    property int mapGridPosY: mapGrid.y

    Image {
        id: mapBg

        anchors {
            centerIn: parent
        }

        source: "qrc:/images/map/tlo_f_1.png"
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
                tileIndex: index
            }
        }
    }

    Item {
        id: charactersContainer

        x: mapGrid.x
        y: mapGrid.y

        Repeater {
            model: features.gameplay.charactersLogic.antenaBoyList

            AntenaBoy {
                antenaBoyModel: modelData
            }
        }

        Timer {
            id: moveTimer

            running: true
            repeat: true
            interval: 15

            onTriggered: {
                features.gameplay.charactersLogic.move()
                features.gameplay.transmissionLogic.checkTransmission()
                features.gameplay.esbekLogic.moveEsbek()
            }
        }
    }

    Item {
        id: esbeksContainer

        x: mapGrid.x
        y: mapGrid.y

        Repeater {
            model: features.gameplay.esbekLogic.esbekList

            Esbek {
                id: esbek

                esbekModel: modelData
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
}

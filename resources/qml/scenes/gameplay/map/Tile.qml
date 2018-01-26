import QtQuick 2.10

import Enums 1.0

Item {
    id: tile

    readonly property QtObject mapModel: features.gameplay.mapModel
    property int tileIndex: -1

    QtObject {
        id: priv

        property QtObject tileModel: null

        readonly property int tileType: tileModel ? tileModel.tileType : TileType.None
    }

    onTileIndexChanged: {
        priv.tileModel = mapModel.getTileByIndex(tileIndex)
    }

    // TODO: replace to image
    Rectangle {
        id: tileImage

        anchors {
            fill: parent
        }

        color: getTileImageSource(priv.tileType)
    }

    function getTileImageSource(tileType) {
        var imageSource = ""
        switch (tileType) {
        case TileType.Headquarter.valueOf():
            imageSource = "red"
            break
        case TileType.Street.valueOf():
            imageSource = "green"
            break
        case TileType.Target.valueOf():
            imageSource = "orange"
            break
        case TileType.Wall.valueOf():
            imageSource = "blue"
            break
        default:
            imageSource = "white"
        }
        return imageSource
    }
}

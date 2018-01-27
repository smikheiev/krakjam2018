import QtQuick 2.10

import Enums 1.0

import "./MapConstants.js" as MapConstants

Item {
    id: tile

    readonly property QtObject mapModel: features.gameplay.mapModel
    property int tileIndex: -1

    width: MapConstants.TILE_SIZE
    height: MapConstants.TILE_SIZE

    QtObject {
        id: priv

        property QtObject tileModel: null

        readonly property int tileType: tileModel ? tileModel.tileType : TileType.None
    }

    onTileIndexChanged: {
        priv.tileModel = mapModel.getTileByIndex(tileIndex)
    }

    Image {
        id: tileImage

        anchors {
            centerIn: parent
        }

        source: getTileImageSource(priv.tileType)
    }

    function getTileImageSource(tileType) {
        var imageSource = ""
        switch (tileType) {
        case TileType.Headquarter:
            imageSource = "qrc:/images/map/HeadQuaters.png"
            break
        case TileType.House:
        case TileType.House_PossibleTarget:
            imageSource = getRandomHouseImage()
            break
        case TileType.Street4x:
            imageSource = "qrc:/images/map/Droga_4x.png"
            break
        case TileType.Street3xBottom:
            imageSource = "qrc:/images/map/Droga_3x_Dol.png"
            break
        case TileType.Street3xTop:
            imageSource = "qrc:/images/map/Droga_3x_Gorna.png"
            break
        case TileType.Street3xLeft:
            imageSource = "qrc:/images/map/Droga_3x_Lewa.png"
            break
        case TileType.Street3xRight:
            imageSource = "qrc:/images/map/Droga_3x_Prawa.png"
            break
        case TileType.StreetCornerLeftBottom:
            imageSource = "qrc:/images/map/Droga_LewyDolnyRog.png"
            break
        case TileType.StreetCornerLeftTop:
            imageSource = "qrc:/images/map/Droga_LewyGorny_Rog.png"
            break
        case TileType.StreetCornerRightBottom:
            imageSource = "qrc:/images/map/Droga_PrawyDolny_Rog.png"
            break
        case TileType.StreetCornerRightTop:
            imageSource = "qrc:/images/map/Droga_PrawyGornyRog.png"
            break
        case TileType.StreetVertical:
            imageSource = "qrc:/images/map/Droga_Pion.png"
            break
        case TileType.StreetHorizontal:
            imageSource = "qrc:/images/map/Droga_poziom.png"
            break
        default:
            imageSource = ""
        }
        return imageSource
    }

    function getRandomHouseImage() {
        var allHouses = [
            "qrc:/images/map/Domki_1DoPoprawki.png",
            "qrc:/images/map/Domki_2DoPoprawki.png",
            ""
        ]
        var rand = Math.floor((Math.random() * allHouses.length))
        return allHouses[rand]
    }
}

#ifndef TILETYPE_H
#define TILETYPE_H

#include <QObject>

class TileTypeEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        Headquarter = 10,
        House1 = 11,
        House2 = 12,
        Street4x = 20,
        Street3xBottom = 21,
        Street3xTop = 22,
        Street3xLeft = 23,
        Street3xRight = 24,
        StreetCornerLeftBottom = 31,
        StreetCornerLeftTop = 32,
        StreetCornerRightBottom = 33,
        StreetCornerRightTop = 34,
        StreetVertical = 41,
        StreetHorizontal = 42,
        PossibleTarget = 100,
        Wall = 200,
    };
    Q_ENUM(Enum)

    static bool isStreet(Enum tileType)
    {
        switch (tileType) {
        case Street3xBottom:
        case Street3xLeft:
        case Street3xRight:
        case Street3xTop:
        case Street4x:
        case StreetCornerLeftBottom:
        case StreetCornerLeftTop:
        case StreetCornerRightBottom:
        case StreetCornerRightTop:
        case StreetHorizontal:
        case StreetVertical:
            return true;
        default:
            return false;
        }
    }
};

typedef TileTypeEnumWrapper::Enum TileType;

#endif // TILETYPE_H

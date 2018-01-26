#ifndef TILETYPE_H
#define TILETYPE_H

#include <QObject>

class TileTypeEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        House,
        MainStreet,
        SecondaryStreet,
    };
    Q_ENUM(Enum)
};

typedef TileTypeEnumWrapper::Enum TileType;

#endif // TILETYPE_H

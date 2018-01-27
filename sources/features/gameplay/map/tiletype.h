#ifndef TILETYPE_H
#define TILETYPE_H

#include <QObject>

class TileTypeEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        Headquarter = 1,
        Street = 2,
        Target = 3,
        Wall = 4,
    };
    Q_ENUM(Enum)
};

typedef TileTypeEnumWrapper::Enum TileType;

#endif // TILETYPE_H

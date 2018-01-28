#ifndef SOUNDTYPE_H
#define SOUNDTYPE_H

#include <QObject>

class SoundTypeEnumWrapper : public QObject
{
    Q_OBJECT

public:
    enum Enum {
        None = 0,
        AntennaBoyCatched,
        SignalTransmitting,
    };
    Q_ENUM(Enum)
};

typedef SoundTypeEnumWrapper::Enum SoundType;

#endif // SOUNDTYPE_H

#ifndef SOUNDSFEATURE_H
#define SOUNDSFEATURE_H

#include <QObject>

#include "soundtype.h"

class SoundsFeature : public QObject
{
    Q_OBJECT

public:
    explicit SoundsFeature(QObject *parent = nullptr);

public slots:
    void onAntennaBoyCatched();
    void onIsSignalTransmittingChanged(bool isTransmitting);

signals:
    void playSound(SoundType sound, bool looped);
    void stopSound(SoundType sound);
};

#endif // SOUNDSFEATURE_H

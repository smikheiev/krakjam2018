#include "soundsfeature.h"

SoundsFeature::SoundsFeature(QObject *parent) : QObject(parent)
{
}

void SoundsFeature::onAntennaBoyCatched()
{
    playSound(SoundType::AntennaBoyCatched, false);
}

void SoundsFeature::onIsSignalTransmittingChanged(bool isTransmitting)
{
    if (isTransmitting)
    {
        playSound(SoundType::SignalTransmitting, true);
    }
    else
    {
        stopSound(SoundType::SignalTransmitting);
    }
}

void SoundsFeature::onObjectiveCompleted()
{
    playSound(SoundType::ObjectiveWon, false);
}

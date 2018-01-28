import QtQuick 2.10
import QtMultimedia 5.8

import Enums 1.0

Item {
    id: soundsPlayer

    readonly property var lastSoundsStarts: ({})

    SoundEffect {
        id: antenaBoyCatchedSound
        source: "qrc:/sounds/siren.wav"
    }

    SoundEffect {
        id: transmittingSound
        source: "qrc:/sounds/390180__debsound__military-communication-loop-37-short.wav"
        volume: 0.6
    }

    SoundEffect {
        id: kozaSound
        source: "qrc:/sounds/57794__reinsamba__1202-goat.wav"
    }

    SoundEffect {
        id: bgSound
        source: "qrc:/sounds/147938__setuniman__military-background-rhythm-0h-wl2k.wav"
        loops: SoundEffect.Infinite
        volume: 0

        Behavior on volume { NumberAnimation {duration: 1000} }
    }

    Connections {
        target: features.sounds
        onPlaySound: {
            console.log("play sound: " + sound + "; " + looped)
            tryPlaySound(sound, looped)
        }
        onStopSound: {
            console.log("stop sound: " + sound)
            tryStopSound(sound)
        }
    }

    function tryPlaySound(soundType, looped) {
        var soundEffect = getSoundEffect(soundType)
        if (!soundEffect) return

        soundEffect.loops = looped ? SoundEffect.Infinite : 0

        if (!soundEffect.playing || isTimeoutBetweenSoundsOk(soundType)) {
            soundEffect.play()
            lastSoundsStarts[soundType] = Date.now()
        }
    }

    function tryStopSound(soundType) {
        var soundEffect = getSoundEffect(soundType)
        if (!soundEffect) return

        soundEffect.stop()
    }

    function getSoundEffect(soundType) {
        switch (soundType) {
        case SoundType.AntennaBoyCatched:
            return antenaBoyCatchedSound
        case SoundType.SignalTransmitting:
            return transmittingSound
        case SoundType.Koza:
            return kozaSound
        }
    }

    function isTimeoutBetweenSoundsOk(soundType) {
        var lastTimePlayed = lastSoundsStarts[soundType]
        if (lastTimePlayed) {
            var minTimeout = getMinSoundTimeout(soundType)
            if (minTimeout < 0) {
                return false
            }

            var diff = Date.now() - lastTimePlayed
            return diff >= minTimeout
        }
        return true
    }

    function getMinSoundTimeout(soundType) {
        switch (soundType) {
        case SoundType.AntennaBoyCatched:
            return 1000
        }
        return -1
    }

    Component.onCompleted: {
        bgSound.play()
        bgSound.volume = 0.8
    }
}

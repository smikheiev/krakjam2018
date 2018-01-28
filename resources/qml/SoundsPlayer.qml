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
        id: jainOpenSound
        source: "qrc:/sounds/jail_open.wav"
    }

    SoundEffect {
        id: transmittingSound
        source: "qrc:/sounds/transmitting.wav"
        volume: 0.6
    }

    SoundEffect {
        id: objectiveWonSound
        source: "qrc:/sounds/won_objective.wav"
    }

    SoundEffect {
        id: kozaSound
        source: "qrc:/sounds/goat.wav"
    }

    SoundEffect {
        id: bgSound
        source: "qrc:/sounds/bg.wav"
        loops: SoundEffect.Infinite
        volume: 0

        Behavior on volume { NumberAnimation {duration: 1000} }
    }

    Connections {
        target: features.sounds
        onPlaySound: {
//            console.log("play sound: " + sound + "; " + looped)
            tryPlaySound(sound, looped)
        }
        onStopSound: {
//            console.log("stop sound: " + sound)
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
        case SoundType.ObjectiveWon:
            return objectiveWonSound
        case SoundType.Koza:
            return kozaSound
        case SoundType.Wiezienie:
            return jainOpenSound
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
        bgSound.volume = 0.4
    }
}

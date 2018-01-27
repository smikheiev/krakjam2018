import QtQuick 2.10

Rectangle {
    id: gameTimer

    property int borderSize: 2
    property int roundTime: features.gameplay.roundTime
    property int progressBarWidth: width - 2 * borderSize
    property bool isPauseMode: false

    signal roundFailed()

    color: "black"

    border.color: "white"
    border.width: borderSize

    Rectangle {
        id: progressBar

        x: borderSize
        y: borderSize
        width: 0
        height: parent.height- 2 * borderSize

        color: "orange"

        NumberAnimation {
           id: progressAnimation

           target: progressBar
           property: "width"
           from: 0
           to: progressBarWidth
           duration: roundTime

           onStopped: {
               if (!isPauseMode) {
                   console.log("onStopped called")
                   roundFailed()
               }
           }
        }
    }

    function startTimer() {
        progressAnimation.restart()
        isPauseMode = false
    }

    function pauseTimer() {
        if (progressAnimation.running) {
            isPauseMode = true
            progressAnimation.pause()
        }
    }
}

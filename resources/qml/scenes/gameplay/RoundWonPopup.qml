import QtQuick 2.10
import QtQuick.Controls 2.2

Rectangle {
    id :roundWonPopup

    property int marginSize: 16

    width: 400
    height: button.y + button.height + marginSize

    color: "black"
    border.color: "red"
    border.width: 2

    Image {
        id: icon

        width: 100
        height: 100
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: marginSize
        }

        source: "qrc:/images/happy.png"
    }

    Text {
        id: textInfo

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: icon.bottom
            topMargin: marginSize
        }

        color: "white"
        text: "Congrats! Hospital was saved!"
    }

    Button {
        id: button

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: textInfo.bottom
            topMargin: marginSize
        }

        text: "START NEXT ROUND"

        onClicked: {
            features.gameplay.newRoundStartNeeded()
            roundWonPopup.opacity = 0.0
        }
    }

    Behavior on opacity {
        NumberAnimation { duration: 500 }
    }
}

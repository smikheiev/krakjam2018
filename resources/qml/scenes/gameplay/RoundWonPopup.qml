import QtQuick 2.10
import QtQuick.Controls 2.2

Image {
    id :roundWonPopup

    property int marginSize: 16

    width: sourceSize.width
    height: sourceSize.height

    source: "qrc:/images/map/bg_popup.png"

    Image {
        id: icon

        width: 100
        height: 100
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: marginSize
        }

        source: "qrc:/images/map/objective_0.png"
    }

    Text {
        id: textInfo

        anchors {
            centerIn: parent
        }

        color: "#FBB03B"
        text: "Congrats!\nNext round is waiting..."
        font.pixelSize: 20
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        id: button

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: marginSize * 2
        }

        text: "START NEXT ROUND"
        font.bold: true

        background: Rectangle {
            anchors {
                fill: parent
            }

            radius: 6

            color: button.pressed ? "#dd9c33" : "#FBB03B"
        }

        onClicked: {
            features.gameplay.newRoundStartNeeded()
            roundWonPopup.visible = false
        }
    }
}

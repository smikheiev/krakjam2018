import QtQuick 2.10

Item {
    id: bottomPanel

    scale: 0.6

    Image {
        id: background

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
        }

        source: "qrc:/images/ui/panelDolny_zielony.png"
    }

    Row {
        id: headsRow

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: background.verticalCenter
            verticalCenterOffset: -15
        }

        spacing: 10

        Repeater {
            id: headsRepeater

            model: features.gameplay.charactersLogic.antenaBoyList

            delegate: Head {
                boyModel: modelData
            }
        }
    }
}

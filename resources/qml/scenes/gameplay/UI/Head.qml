import QtQuick 2.10
import QtGraphicalEffects 1.0

Item {
    id: head

    property QtObject boyModel

    readonly property int boyId: boyModel ? boyModel.id : -1
    readonly property bool isSelected: boyModel ? boyModel.isSelected : false
    readonly property bool isInactive: boyModel ? boyModel.isInactive : false

    width: headImage.width
    height: headImage.height

    scale: isSelected ? 0.85 : 0.75

    onIsInactiveChanged: {
        if (!isInactive) {
            opacity = 1
        }
    }

    Image {
        id: headImage

        anchors {
            centerIn: parent
        }

        source: getImageSource(boyId, isSelected)
    }

    SequentialAnimation {
        id: inactiveAnimation

        running: isInactive
        loops: Animation.Infinite

        NumberAnimation { target: head; property: "opacity"; duration: 250; from: 1; to: 0 }
        NumberAnimation { target: head; property: "opacity"; duration: 250; from: 0; to: 1 }
    }

    function getImageSource(boyId) {
        return "qrc:/images/ui/Glowa_" + boyId + "_" + (isSelected ? "wybrana" : "niewybrana") + ".png"
    }
}

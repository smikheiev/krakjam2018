import QtQuick 2.10
import QtGraphicalEffects 1.0

Item {
    id: head

    property QtObject boyModel

    readonly property int boyId: boyModel ? boyModel.id : -1
    readonly property bool isSelected: boyModel ? boyModel.isSelected : false

    width: headImage.width
    height: headImage.height

    scale: isSelected ? 0.85 : 0.75

    Image {
        id: headImage

        anchors {
            centerIn: parent
        }

        source: getImageSource(boyId, isSelected)
        visible: !isSelected
    }

    BrightnessContrast {
        anchors {
            fill: headImage
        }
        source: headImage
        brightness: 0.7
        contrast: 0.8
        cached: true
        visible: isSelected
    }

    function getImageSource(boyId) {
        return "qrc:/images/ui/Glowa_" + boyId + "_niewybrana.png"
    }
}

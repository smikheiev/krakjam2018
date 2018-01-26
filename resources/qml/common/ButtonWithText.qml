import QtQuick 2.10
import QtQuick.Controls 2.2

Button {
    id: buttonWithText

    property string textString: ""

    Text {
        id: playText

        anchors {
            centerIn: parent
        }

        text: textString
        font {
            family: fonts.trebuchet
            pointSize: 20
        }
    }
}

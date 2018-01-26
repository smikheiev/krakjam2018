import QtQuick 2.10

Item {
    id: fonts

    property string trebuchet: trebuchetFont.name

    FontLoader {
        id: trebuchetFont

        name: "Trebuchet MS"
    }
}

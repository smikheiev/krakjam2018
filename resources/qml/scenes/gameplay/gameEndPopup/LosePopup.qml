import QtQuick 2.10

import Enums 1.0

BaseGameEndPopup {
    id: losePopup

    popupGameplayState: GameplayState.Lose
    imageSource: "qrc:/images/sad.png"
}

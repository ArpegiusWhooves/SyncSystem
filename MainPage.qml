import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Item {
    id: mainPage
    property alias dialValue: dial.value
    property alias delayButtonChecked: delayButton.checked
    property alias sliderValue: slider.value
    property alias elementChecked: element.checked
    property alias check_masterChecked: check_master.checked

    CheckBox {
        id: check_master
        x: 39
        y: 28
        text: qsTr("Slave/Master")
    }

    DelayButton {
        id: delayButton
        x: 353
        y: 82
        text: qsTr("Delay Button")
    }

    Dial {
        id: dial
        x: 364
        y: 138
    }

    Slider {
        id: slider
        x: 56
        y: 182
        stepSize: 0.01
        value: 0.5
    }

    Switch {
        id: element
        x: 83
        y: 282
        text: qsTr("Switch")
    }
}















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

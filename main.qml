import QtQuick 2.12
import QtQuick.Window 2.12
import SyncSystem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SyncClient {
        id: sync
        slave: mainPage.check_masterChecked
        Component.onCompleted: sync.configure({});
    }

    MainPage {
        id: mainPage
//        property alias dialValue: dial.value
//        property alias delayButtonChecked: delayButton.checked
//        property alias sliderValue: slider.value
//        property alias elementChecked: element.checked
//        property alias check_masterChecked: check_master.checked
        dialValue: dialValueState.value || 0.0
        onDialValueChanged: dialValueState.value = mainPage.dialValue
        SyncState {
            objectName: "dialValue"
            id: dialValueState
            parentState: sync
        }
        SyncState on delayButtonChecked {
            parentState: sync
        }
//        sliderValue: sliderValueState.value || 0.0
//        SyncState {
//            objectName: "sliderValue"
//            id: sliderValueState
//            value:  mainPage.sliderValue
//            parentState: sync
//        }
        SyncState on sliderValue {
            parentState: sync
        }
        SyncState on elementChecked {
            parentState: sync
        }

    }
}

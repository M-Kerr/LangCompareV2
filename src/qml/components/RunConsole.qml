import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Item {
    id: root
    anchors.bottom: parent.bottom
    width: parent.width
    state: "off"

    property alias textArea: textArea
    property alias transition: transition

    states: [
        State {
            name: "on"
            AnchorChanges { target: root; anchors.top: parent.top }
            PropertyChanges { target: root; opacity: 1.0 }
        },

        State {
            name: "off"
            AnchorChanges { target: root; anchors.top: parent.bottom }
            PropertyChanges { target: root; opacity: 0.0; }
        }
    ]

    transitions: Transition {
        id: transition
        ParallelAnimation {
            AnchorAnimation { duration: 250}
//            AnchorAnimation { duration: 250; easing: Easing.OutExpo}
            SmoothedAnimation{ target: root; property: "opacity";
                velocity: 1.5;
//                easing: Easing.OutExpo; velocity: 1.5;
            }
        }
    }

    ScrollView {
        id: scrollView
        objectName: "scrollView"
        anchors.fill: parent

        TextArea {
            id: textArea
            objectName: "textArea"
            width: parent.width
            wrapMode: TextEdit.Wrap
            focus: false
            readOnly: true
            selectByMouse: true

            background: Rectangle {
                id: backgroundID
                color: "white"
                border.width: 1
                border.color: "gray"
                opacity: 0.8
            }

            Action {
                id: copyAction
                shortcut: "Ctrl+C"
                onTriggered: textArea.copy()
            }
        }
    }
}

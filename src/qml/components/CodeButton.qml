import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Code 1.0

Item {
    id: root
    width: round_button.width
    height: round_button.height
    property var color
    property string language
    property string file
    property int iters
    property int limit
    property double radius: round_button.height / 10
    property alias button: round_button
    property alias text: txt
    property alias code: code_element

    Behavior on x { SpringAnimation { spring: 3; damping: 0.25; } }
    Behavior on y { SpringAnimation { spring: 3; damping: 0.25; } }

    RoundButton {
        id: round_button

        anchors.centerIn: parent
        width: 130
        height: 40
        radius: root.radius
        clip: true
        Material.elevation: 1
        Material.background: color

        Text {
            id: txt
            text: code_element.file_name()
            font {pointSize: 15}
            anchors.centerIn: parent
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.verticalCenter: parent.verticalCenter
        }

        Code {
            id: code_element
            language_: root.language
            file_: root.file
            iters_: root.iters
            limit_: root.limit
        }
    }
}

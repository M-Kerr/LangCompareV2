import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Page {

    property int minimumWidth
    property int minimumHeight

    Label {
        anchors.centerIn: parent
        text: "Chartz here"
        font {bold: true; pixelSize: 25}
    }
}

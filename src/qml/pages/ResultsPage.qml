import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Page {

    property int minimumWidth
    property int minimumHeight

    Label {
        anchors.centerIn: parent
        text: "Chartz here"
        font {bold: true; pixelSize: 25}
    }
}

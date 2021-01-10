import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import "pages"

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex


        AddCodePage{
        }

        EditCodePage {
        }

        ResultsPage {
        }

    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Add")
        }

        TabButton {
            text: qsTr("Edit")
        }

        TabButton {
            text: qsTr("Results")
        }

    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "pages"

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")
    id: window

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

    header: ColumnLayout {
        width: window.width

        TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex

            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: 7

            TabButton {
                id: add_tab
                text: qsTr("Add")
            }

            TabButton {
                id: edit_tab
                text: qsTr("Edit")
            }

            TabButton {
                id: results_tab
                text: qsTr("Results")
            }
        }


        // Run status box will go here

    }

    footer: ColumnLayout {
        width: window.width
        //TODO: make footer invisible until running is an option

        Button {
            text: "Run"
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 50
            Layout.bottomMargin: 30
            Layout.preferredWidth: 100
        }

    }
}

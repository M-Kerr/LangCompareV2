import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "pages"
import Languages 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")
    id: window

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
                text: qsTr("Select")
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

    }
        SwipeView {
            id: swipeView
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            AddCodePage{
                fDialog.onAccepted: {
                    runButton.enabled = true
                }
            }

            EditCodePage {
            }

            ResultsPage {
            }

        }

        ScrollView {
        //TODO: compile/run status box will go here
            id: scrollView
            z: 1
            visible: true
//            visible: false
            anchors.fill: parent

            TextArea {
                id: textArea
                focus: false
                activeFocusOnPress: false
                activeFocusOnTab: false
                color: "white"

                text: "Foo fumm fii faaa fiizzz asdf \n
Fim fum foo fooo hello these are multiple \n lines of output"

                background: Rectangle {
                    color: "#3F51B5"
                }

            }

        }


    footer: ColumnLayout {
        width: window.width
        //TODO: make footer invisible until running is an option

        Button {
            id: runButton
            text: "Run"
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 50
            Layout.bottomMargin: 30
            Layout.preferredWidth: 100
            enabled: false
            opacity: 0.60
            onEnabledChanged: {
                if (enabled) opacity = 1
                else opacity = 0.6
            }

            onClicked: {
                scrollView.visible = true
                //TODO: start compilation and execution
            }
        }

    }
}

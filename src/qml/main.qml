import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "pages"
import "components"

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("LangCompare")
    id: root

    minimumWidth: swipeView.currentItem.minimumWidth
    minimumHeight: {
        swipeView.currentItem.minimumHeight + header.height
                + footer.height + 40
    }

    property int read_fd
    property int write_fd

    property alias cModel: selectPage.cModel

    function openPipe() {
        Languages.open_pipe();
        read_fd = Languages.read_fd_;
        write_fd = Languages.write_fd_;
    }

    function execute() {
        runConsole.transition.runningChanged.disconnect(root.execute)
        cModel.executeCode(read_fd, write_fd)
    }

    Component.onCompleted: openPipe()

    header: ColumnLayout {
        width: root.width

        TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex

            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: 7

                // Add tabs when additional pages are implemented
//            TabButton {
//                id: selectTab
//                text: qsTr("Select")
//            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SelectPage{
            id: selectPage
            fDialog.onAccepted: {
                runButton.enabled = true
            }
        }
    }

    RunConsole {
        id: runConsole
        objectName: "runConsole"

        Component.onCompleted: {
            Languages.new_message.connect(textArea.append)
        }

            Timer {
            id: runConsoleOffTimer
            interval: 250
            running: false

            onTriggered: runConsole.state = "off"
        }
    }

    footer: ColumnLayout {
        width: root.width

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
                runConsole.state = "on"
                visible = false
                minimizeConsole.visible = true

                // wait for console transition animations to complete
                // before compile-run
                runConsole.transition.runningChanged.connect(root.execute)
            }
        }

        Button {
            id: minimizeConsole
            text: "⇣"
            font {bold: true}
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 50
            Layout.bottomMargin: 30
            Layout.preferredWidth: 100
            visible: false

            onClicked: {
                runConsoleOffTimer.running = true
                visible = false
                runButton.visible = true
            }
        }

    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Page {
    id: root
    width: 600
    height: 400

    ColumnLayout {
        id: columnLayout
        //        anchors.top: parent.top
        anchors.topMargin: root.height * 0.15
        //        width: parent.width
        anchors.fill: parent

        ComboBox {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 200;
            anchors.bottomMargin: root.height * 0.05

            displayText: "Select a Language"
            model: LANGUAGES

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                }
                onRejected: {
                    console.log("Canceled")
                }
                //TODO visible = true set by ComboBox
                //TODO    folder: //Code/lanuguage dir
                sidebarVisible: false
            }
        }

        // THe model is our C++ vector<Code*>

        GridView {
            id: gridView
            Layout.fillHeight: true

            //            add: Transition {
            //                NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
            //            }
            //            remove: Transition {
            //                ParallelAnimation {
            //                    NumberAnimation { property: "opacity"; to: 0; duration: 1000 }
            //                    NumberAnimation { properties: "x,y"; to: 100; duration: 1000 }
            //                }
            //            }
//            removeDisplaced: Transition {
//                NumberAnimation { properties: "x,y"; duration: 1000 }
//            }
        }
    }
}

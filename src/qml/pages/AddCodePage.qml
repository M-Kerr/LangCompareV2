// TODO: Have to implement Iters and timeout selection
// Before building the Code*
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import Languages 1.0
import Code 1.0

Page {
    id: root
    width: 600
    height: 400

    ColumnLayout {
        id: columnLayout
        anchors.topMargin: root.height * 0.15
        anchors.fill: parent

        ComboBox {
            id: comboBox
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 200;
            anchors.bottomMargin: root.height * 0.05

            displayText: "Select a Language"
            // FIXME: Make sure the map key is represented in the model
            model: LANGUAGES

            onActivated: {
                console.log(currentText + " selected")
                fileDialog.visible = true
            }


            FileDialog {
                id: fileDialog
                title: "Please choose a file"

                onAccepted: {
                    //TODO delete all debug prints
                    console.log("You chose: " + fileDialog.fileUrls)
                    console.log("Language: " + comboBox.currentText)
                    Languages.qml_build_code_list(comboBox.currentText,
                                                  fileUrl.toString(), null)

                    // filename parent iters timeout
                }
                onRejected: {
                    console.log("Canceled")
                }
                //TODO visible = true set by ComboBox
                //TODO    folder: //Code/lanuguage dir
            }
        }

        // The model is our C++ vector<Code*>

        GridView {
            id: gridView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: code_files
            delegate: Rectangle {
                id: rec
                height: 25; width: 100
                color: "red"
                required property string language_

                Text {text: rec.language_}
            }

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

//TODO: add iters and limit support
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtQml.Models 2.15
import Languages 1.0
import Code 1.0
import "../components"
import "../components/create_code_button.js" as Code_js

Page {
    id: root
    width: 600
    height: 400

    Component {
        id: codeButtonComponent
        CodeButton {}
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: root.height * 0.08
        spacing: 20

        GridLayout {
            id: topGridLayout
            Layout.alignment: Qt.AlignHCenter
            height: parent.height / 3
            rows: 2
            columns: 3
            columnSpacing: 10
            rowSpacing: 10

            ComboBox {
                id: comboBox
                Layout.preferredWidth: 200;
                displayText: "Select a Language"
                model: LANGUAGES

                onActivated: {
                    fileDialog.visible = true
                }

                FileDialog {
                    id: fileDialog
                    title: "Please choose a file"
                    //TODO    folder: //Code/lanuguage dir

                    signal codeObjectReady (string language, url file,
                                            int iters, int limit)

                    onAccepted: {
                        codeObjectReady(comboBox.currentText, fileUrl, 1, 0)
                    }

                    onRejected: {
                        console.log("Canceled")
                    }
                }
            }

            TextField {
                id: itersInput
                placeholderText: "Enter Iterations"
            }

            TextField {
                id: timeoutInput
                placeholderText: "Enter timeout"
            }

            // Aligns RoundButton to rightmost column
            Item {width: acceptButton.width; height: acceptButton.height}
            Item {width: acceptButton.width; height: acceptButton.height}

            Button {
                //            RoundButton {
                id: acceptButton
                width: buttonText.width + 10
                height: buttonText.height + 10
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                //                width: 200; height: 50
                //                radius: width / 8

                Text {
                    id: buttonText
                    anchors.centerIn: parent
                    text: "Accept"
                }
            }
        }

        GridLayout {
            id: bottomGridLayout
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            columnSpacing: 10
            rows: 1

            GroupBox {
                Layout.alignment: Qt.AlignHCenter

                label: Label {
                    text: "C++"
                    horizontalAlignment: Text.AlignHCenter
                }

                GridView {
                    id: cpp_grid_view
                    flow: GridView.FlowTopToBottom

                    model: ObjectModel {
                        id: cpp_code_model

                        Component.onCompleted: {
                            fileDialog.codeObjectReady.connect(codeObjectReadySlot)
                        }

                        function codeObjectReadySlot (language, file, iters, limit)
                        {
                            if (language === "c++")
                                cpp_code_model.append(
                                            codeButtonComponent.createObject(
                                                this,
                                                { language: comboBox.currentText,
                                                    file: file, iters: iters,
                                                    limit: limit
                                                }))
                        }
                    }
                    //                model: code_files


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


            GroupBox {
                Layout.alignment: Qt.AlignHCenter

                label: Label {
                    text: "Python++"
                    horizontalAlignment: Text.AlignHCenter
                }

                GridView {
                    id: python_grid_view
                    flow: GridView.FlowTopToBottom
                    Layout.alignment: Qt.AlignHCenter

                    model: ObjectModel {
                        id: python_code_model

                        Component.onCompleted: {
                            fileDialog.codeObjectReady.connect(codeObjectReadySlot)
                        }

                        function codeObjectReadySlot (language, file, iters, limit)
                        {
                            if (language === "python")
                                python_code_model.append(
                                            codeButtonComponent.createObject(
                                                this,
                                                { language: comboBox.currentText,
                                                    file: file, iters: iters,
                                                    limit: limit
                                                }))
                        }
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
    }
}


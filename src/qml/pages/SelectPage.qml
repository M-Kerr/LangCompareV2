import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtQml.Models 2.15
import Languages 1.0
import Code 1.0
import "../components"
import "../components/create_code_button.js" as Code_js
import QtQuick.Controls.Material 2.15

Page {
    id: page
    width: 600
    height: 400

    property alias fDialog: fileDialog
    property alias cModel: code_model

    Component {
        id: codeButtonComponent
        CodeButton {}
    }

    ObjectModel {
        id: code_model
        function executeCode(read_fd, write_fd) {
            // Iterate through the model and execute Code objects
            for (var i=0; i < count; i++)
            {
                get(i).code.execute(read_fd, write_fd);
            }
            for (i=0; i < count; i++)
            {
                get(i).code.print_results();
            }
            // TODO: render results
        }
    }

    Item {
        id: root
        anchors.fill: parent
        Item {
            id: topBox
            anchors.top: root.top
            width: parent.width
            height: parent.height / 3
            anchors.topMargin: root.height * 0.08

            GridLayout {
                id: topGridLayout
                anchors.centerIn: parent
                rows: 2
                columns: 3
                columnSpacing: 10
                rowSpacing: 10

                ComboBox {
                    property string instruction: "Select a Language"
                    property var colors: {
                        "c++": "#F44336",       // Material.red
                        "python": "#2196F3"     // Material.blue
                    }
                    id: comboBox
                    Layout.preferredWidth: 200;
                    displayText: instruction
                    model: LANGUAGES


                    delegate: ItemDelegate {
                        text: modelData
                        width: parent.width

                        Rectangle {
                            anchors.fill: parent
                            color: comboBox.colors[modelData]
                            opacity: 0.15
                        }
                    }

                    onActivated: {
                        displayText = currentText
                        acceptButton.enabled = true
                        if (currentText === "c++")
                        {
                            fileDialog.folder = "file://" + ExecutableDir + "/code/cpp"
                            Material.background = Qt.lighter(colors["c++"], 1.70)
                        } else if (currentText === "python")
                        {
                            fileDialog.folder = "file://" + ExecutableDir + "/code/py"
                            Material.background = Qt.lighter(colors["python"], 1.80)
                        }
                    }

                    FileDialog {
                        id: fileDialog
                        title: "Please choose a file"

                        signal codeObjectReady (string language, url file,
                                                int iters, int limit)

                        onAccepted: {
                            var iters_ = parseInt(itersInput.text, 10)
                            var limit_ = parseInt(timeoutInput.text, 10)
                            iters_ = (iters_ > 1) ? iters_ : 1
                            limit_ = (limit_ > 0) ? limit_ : 0

                            code_model.append(
                                        codeButtonComponent.createObject(
                                            code_grid_view,
                                            { language: comboBox.currentText,
                                                file: fileUrl, iters: iters_,
                                                limit: limit_, color: comboBox.Material.background
                                            }))

                            itersInput.clear()
                            timeoutInput.clear()
                            comboBox.displayText = comboBox.instruction
                            comboBox.Material.background = root.Material.background
                            acceptButton.enabled = false
                        }

                    }
                }

                TextField {
                    id: itersInput
                    placeholderText: "Iterations"
                }

                TextField {
                    id: timeoutInput
                    placeholderText: "Timeout (ms)"
                }

                // Aligns acceptButton to rightmost column
                Item {width: acceptButton.width; height: acceptButton.height}
                Item {width: acceptButton.width; height: acceptButton.height}

                Button {
                    id: acceptButton
                    width: buttonText.width + 10
                    height: buttonText.height + 10
                    Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                    enabled: false
                    opacity: 0.50
                    onEnabledChanged: {
                        if (enabled) opacity = 1
                        else opacity = 0.50
                    }

                    onClicked: {
                        fileDialog.visible = true
                    }

                    Text {
                        id: buttonText
                        anchors.centerIn: parent
                        text: "Accept"
                    }
                }
            }
        }

        Item {
            id: bottomBox
            anchors.top: topBox.bottom
            anchors.bottom: root.bottom
            width: root.width

            GridView {
                id: code_grid_view
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                anchors.topMargin: 20
                anchors.bottomMargin: 20

                cellWidth: 135
                cellHeight: 50

                model: code_model
            }
        }
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



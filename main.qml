import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import QtQuick.LocalStorage
import QtQuick.Layouts

Window {
    id: mainApplicationWindow
    width: Screen.desktopAvailableWidth / 2
    height: Screen.desktopAvailableHeight / 2
    visible: true
    title: qsTr("File hexer")
    color: mainBackColor

    readonly property real textFieldMinimumWidth: mainApplicationWindow.width / 4
    readonly property real butttonMinimumWidth: mainApplicationWindow.width / 8
    readonly property color mainBackColor: "#ffe4b5"
    readonly property color itemsColor: "#daa520"

    ColumnLayout  {
        id: settingsLayout

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height / 30
        anchors.leftMargin: parent.width / 30

        TextField {
            id: maskInputFiles
            Layout.minimumWidth: textFieldMinimumWidth
            Layout.alignment: Qt.AlignLeft
            placeholderText: "Enter the mask of the input files"
        }

        CheckBox {
            id: checkDelInputFile
            Layout.alignment: Qt.AlignLeft
            text: qsTr("Delete input file")
        }

        RowLayout {
            Layout.alignment: Qt.AlignLeft

            TextField {
                id: folderInput
                Layout.minimumWidth: textFieldMinimumWidth
                Layout.alignment: Qt.AlignLeft
                placeholderText: "Enter the path to the input files"
            }

            Button {
                Layout.minimumWidth: butttonMinimumWidth
                text: qsTr("Choose a path")
                onClicked: filePathChooser.open()
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignLeft

            Label {
                text: qsTr("Actions when repeating the file name: ")
            }

            RadioButton {
                id: overwriteFilesCheck
                checked: true
                text: qsTr("Overwrite files")
            }
            RadioButton {
                text: qsTr("Modify file names")
            }
        }

        ColumnLayout {

            Label {
                text: qsTr("Frequency of checking for the presence of input files (sec): ")
            }

            SpinBox {
                id: frequencyTime
                Layout.alignment: Qt.AlignLeft
            }
        }


        ColumnLayout {
            Layout.alignment: Qt.AlignLeft

            Label {
                text: qsTr("File modification methods: ")
            }
            ButtonGroup { id: rBgModeroup }
            RadioButton {
                checked: true
                text: qsTr("XOR")
                ButtonGroup.group: rBgModeroup
            }
            RadioButton {
                id: rb1
                text: qsTr("empty")
                ButtonGroup.group: rBgModeroup
            }
            RadioButton {
                id: rb2
                text: qsTr("empty")
                ButtonGroup.group: rBgModeroup
            }
            RadioButton {
                id: rb3
                text: qsTr("empty")
                ButtonGroup.group: rBgModeroup
            }
            RadioButton {
                id: rb4
                text: qsTr("empty")
                ButtonGroup.group: rBgModeroup
            }
        }

    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: parent.height / 30
        anchors.rightMargin: parent.width / 30

        Button {
            width: butttonMinimumWidth
            Layout.alignment: Qt.AlignLeft
            text: qsTr("Set up settings and start")

            onClicked: {
                setUpSettings(maskInputFiles.text, checkDelInputFile.checked, folderInput.text, overwriteFilesCheck.checked,
                              frequencyTime.value, 0);
            }
        }
    }




    FilePathChooser{
        id: filePathChooser
    }
}

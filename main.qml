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
    property string rbClicked; property real rbClickedNum;
    property bool timerSetUpSettingsRepeat: false
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

        TextField {
            id: fieldIEnencryptionKey
            Layout.minimumWidth: textFieldMinimumWidth
            Layout.alignment: Qt.AlignLeft
            inputMask: "00000000000000000000"
            placeholderText: "Enter the encryption key"
        }

        CheckBox {
            id: checkDelInputFile
            Layout.alignment: Qt.AlignLeft
            text: qsTr("Delete input file")
            checkState: Qt.Checked
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
                id: modifyFileNamesCheck
                text: qsTr("Modify file names")
            }
        }

        ColumnLayout {

            Label {
                text: qsTr("Frequency of checking for the presence of input files (sec).
                                       if the value is 0 - one-time launch: ")
            }

            SpinBox {
                id: frequencyTime
                Layout.alignment: Qt.AlignLeft
                to:10
            }
        }


        ColumnLayout {
            Layout.alignment: Qt.AlignLeft

            Label {
                text: qsTr("File modification methods: ")
            }
            ButtonGroup {
                id: rBgModegroup
                exclusive: true;
            }
            RadioButton {
                id: rb0
                checked: true
                text: qsTr("1) XOR")
                ButtonGroup.group: rBgModegroup
            }
            RadioButton {
                id: rb1
                text: qsTr("2) empty")
                ButtonGroup.group: rBgModegroup
            }
            RadioButton {
                id: rb2
                text: qsTr("3) empty")
                ButtonGroup.group: rBgModegroup
            }
            RadioButton {
                id: rb3
                text: qsTr("4) empty")
                ButtonGroup.group: rBgModegroup
            }
            RadioButton {
                id: rb4
                text: qsTr("5) empty")
                ButtonGroup.group: rBgModegroup
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
                rbClicked = rBgModegroup.checkedButton.text;
                rbClickedNum = rbClicked.charAt(0);

                if(setUpSettings(maskInputFiles.text, fieldIEnencryptionKey.text, checkDelInputFile.checked, folderInput.text,
                                 overwriteFilesCheck.checked, rbClickedNum))
                {
                    pushSetUpSettingsTimer.start()
                }
            }
        }
    }

    Item {
        Timer {
            id: pushSetUpSettingsTimer
            interval: frequencyTime * 1000;
            running: frequencyTime > 0 ? true : false;
            repeat: timerSetUpSettingsRepeat ? true : false
            onTriggered: {
                setUpSettings(maskInputFiles.text, fieldIEnencryptionKey.text, checkDelInputFile.checked, folderInput.text,
                                       overwriteFilesCheck.checked, rbClickedNum)
                timerSetUpSettingsRepeat: false
        }

        Text { id: time }
    }


    FilePathChooser{
        id: filePathChooser
    }
}

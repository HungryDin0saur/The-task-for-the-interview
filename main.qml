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

    readonly property real textFieldMinimumWidth: mainApplicationWindow.width / 4
    readonly property color mainBackColor: "#ffe4b5"
    readonly property color itemsColor: "#daa520"

    color: mainBackColor


    ColumnLayout  {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height / 30
        anchors.leftMargin: parent.width / 30

        TextField {
            Layout.minimumWidth: textFieldMinimumWidth
            Layout.alignment: Qt.AlignLeft
            placeholderText: "Enter the mask of the input files"
        }

        CheckBox {
            Layout.alignment: Qt.AlignLeft
            text: qsTr("Delete input file")
        }

        RowLayout {
            Layout.alignment: Qt.AlignLeft

            TextField {
                Layout.minimumWidth: textFieldMinimumWidth
                Layout.alignment: Qt.AlignLeft
                placeholderText: "Enter the path to the input files"
            }

        }

    }


}

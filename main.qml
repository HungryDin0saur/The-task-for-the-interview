import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Window
import QtQuick.LocalStorage


Window {
    id: mainApplicationWindow
    width: Screen.desktopAvailableWidth / 2
    height: Screen.desktopAvailableHeight / 2
    visible: true
    title: qsTr("File hexer")

    readonly property color mainBackColor: "#0000cd"

    Page {
        width: mainApplicationWindow
        height: mainApplicationWindow
        anchors.fill: parent
        //color: mainBackColor

        TextInput {
            width: parent.width / 4
            height: parent.height / 4
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: parent.height / 30
            anchors.leftMargin: parent.width / 30

            text: "TEST"
        }
    }
}

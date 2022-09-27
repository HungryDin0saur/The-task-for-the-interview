import QtQuick
import QtQuick.Dialogs

FileDialog {
    nameFilters: [maskInputFiles.text]

    onAccepted: {
       console.log()
    }
}

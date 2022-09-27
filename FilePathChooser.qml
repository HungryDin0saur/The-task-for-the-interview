import QtQuick
import QtQuick.Dialogs

FileDialog {
    nameFilters: [maskInputFiles.text]
    fileMode: FileDialog.OpenFiles

    onAccepted: {

       console.log(currentFiles)
    }
}

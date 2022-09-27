import QtQuick
import QtQuick.Dialogs


FolderDialog {

    onAccepted: {
       console.log(currentFolder)
    }
}

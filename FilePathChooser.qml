import QtQuick
import QtQuick.Dialogs


FolderDialog {
    onAccepted: {
       folderInput.text = currentFolder
    }
}

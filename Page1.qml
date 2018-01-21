import QtQuick 2.7
import QtQuick.Dialogs 1.2

Page1Form {
    buttonChangePort.onClicked: {
        console.log("Button Change Port Pressed. Entered port: " + textFieldPort.text);
        signalServerPortChanged(textFieldPort.text);
    }

    buttonChoosePath.onClicked: {
        fileDialogPath.open();
    }

    fileDialogPath.onAccepted: {
        console.log("Accepted path: " + fileDialogPath.folder);
        var path = fileDialogPath.folder.toString().substring(7);
        console.log("Accepted path will be: " + path);
        textFieldPath.text = path;
    }

    buttonAcceptPath.onClicked: {
        console.log("Button Accepth Path Pressed. Entered path: " + textFieldPath.text);
        signalRootDirPathChanged(textFieldPath.text);
    }
}

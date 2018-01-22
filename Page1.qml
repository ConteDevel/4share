import QtQuick 2.7
import QtQuick.Dialogs 1.2

Page1Form {
    buttonChangePort.onClicked: {
        var port = textFieldPort.text;
        console.log("Button Change Port Pressed. Entered port: " + port);
        if (port > 1023 && port <= 65535 ) {
            signalServerPortChanged(textFieldPort.text);
        }
        else {
            messageDialogError.setText("Введено некорректное значение порта!")
            messageDialogError.open();
        }
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

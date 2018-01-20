import QtQuick 2.7

Page1Form {
    buttonChangePort.onClicked: {
        // TODO: validate
        console.log("Button Pressed. Entered text: " + textFieldPort.text);
        signalServerPortChanged(textFieldPort.text);
    }
}

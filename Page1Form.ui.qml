import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias buttonChangePort: buttonChangePort
    property alias textFieldPort: textFieldPort

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top

        Text {
            text: "Порт, прослушиваемый сервером:"
        }

        TextField {
            id: textFieldPort
            objectName: "obj_textfieldport"
            font.family: "Ubuntu"
            renderType: Text.QtRendering
            font.weight: Font.Black
            placeholderText: qsTr("Порт")
        }

        Button {
            id: buttonChangePort
            text: "Изменить порт"
        }
    }
}

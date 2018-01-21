import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3

Item {
    property alias buttonChangePort: buttonChangePort
    property alias textFieldPort: textFieldPort
    property alias textFieldPath: textFieldPath
    property alias buttonChoosePath: buttonChoosePath
    property alias buttonAcceptPath: buttonAcceptPath
    property alias fileDialogPath: fileDialogPath

    RowLayout {
        id: rowLayoutPort
        x: 20
        width: 600
        height: 40
        anchors.topMargin: 20
        anchors.top: parent.top

        Text {
            text: "Порт, прослушиваемый сервером:"
        }

        TextField {
            id: textFieldPort
            Layout.fillWidth: false
            objectName: "obj_textfieldport"
            font.family: "Ubuntu"
            renderType: Text.QtRendering
            font.weight: Font.Black
            placeholderText: qsTr("Порт")
        }

        Button {
            id: buttonChangePort
            text: "Изменить порт"
            Layout.fillWidth: true
        }
    }

    RowLayout {
        id: rowLayoutPath
        x: 20
        width: 600
        height: 40
        anchors.topMargin: 20
        anchors.top: rowLayoutPort.bottom

        Text {
            text: "Путь к корневой директории:"
        }

        TextField {
            id: textFieldPath
            Layout.fillWidth: true
            objectName: "obj_textfieldpath"
            font.family: "Ubuntu"
            renderType: Text.QtRendering
            font.weight: Font.Black
            placeholderText: qsTr("Путь к директории")
            readOnly: true
        }
    }
    RowLayout {
        id: rowLayoutPath2
        x: 20
        width: 600
        height: 40
        anchors.topMargin: 20
        anchors.top: rowLayoutPath.bottom

        Button {
            id: buttonChoosePath
            x: 20
            width: 250
            text: "Выбрать путь ..."
            Layout.fillWidth: true
        }

        Button {
            id: buttonAcceptPath
            x: 350
            width: 250
            text: "Изменить корневой путь"
            Layout.fillWidth: true
        }

        FileDialog {
            id: fileDialogPath
            title: "Выберите корневую директорию доступа"
            folder: shortcuts.home
            selectFolder: true
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

ApplicationWindow {
    visible: true
    width: 640
    height: 250
    title: qsTr("4Share - Управление компьютером в локальной сети")
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2

    signal signalServerPortChanged(string newPort)
    signal signalRootDirPathChanged(string newPath)

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Text {
                id: textLogger
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: 20
                text: "Сообщения в журнале логирования:"
            }

            ListView {
                id: listView

                anchors.top: textLogger.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25
                anchors.rightMargin: 10
                anchors.topMargin: 15
                anchors.bottomMargin: 10

                delegate: Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 30

                    text: modelData
                }

                model: listModel
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Управление")
        }
        TabButton {
            text: qsTr("Журнал логов")
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("4Share - Управление компьютером в локальной сети")

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
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: 80
                text: "Сообщения в журнале логирования:"
            }

            ListView {
                id: listView

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 45

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

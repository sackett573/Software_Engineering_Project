import QtQuick 2.3
import QtQuick.Controls 1.2
import TextViewer 1.0
import Document 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Sidebar
    {
        id: sidePanel
    }

    TextViewer
    {
        fillColor: "#FFFFFF"
        document: AppData.document
        anchors.left : sidePanel.right
        anchors.top : parent.top
        anchors.bottom : parent.bottom
        anchors.right : parent.right
    }
}

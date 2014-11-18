import QtQuick 2.3
import QtQuick.Controls 1.2
import TextViewer 1.0
import Document 1.0

ApplicationWindow {
    id: mainApp
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    menuBar: MenuBar {
        id: menu
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

    Rectangle
    {
        anchors.left: sidePanel.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: "#FFFFFF"
        ScrollView
        {
            id: scroll
            anchors.fill: parent
            TextViewer
            {  
                id: viewer
                x: sidePanel.x
                y: sidePanel.y
                width: 1000
                height: 1000
                clip: true
                fillColor: "#FFFFFF"
                document: AppData.document
            }
        }

        MouseArea
        {
            anchors.fill : parent
            onPressed: {
                var val = viewer.getNewSelection(mouseX, mouseY);
                AppData.cursorPosition = val;
                viewer.cursorPos = val;
                viewer.update();
            }
        }
    }
}

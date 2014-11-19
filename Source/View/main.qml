import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0
import TextViewer 1.0
import Document 1.0

ApplicationWindow {
    id: mainApp
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    FileDialog
    {
        id: filePicker
        title: "Please Choose a File"
        selectMultiple: false
        selectFolder: false
        selectExisting: true
        onAccepted:
        {
            AppData.open_document(fileUrl);
            visible = false;
        }
        onRejected:
        {
            visible = false;
        }
    }

    menuBar: MenuBar {
        id: menu
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered:
                {
                    filePicker.visible = true;
                }
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
        id: textRect
        anchors.top: parent.top
        anchors.left: sidePanel.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#FFFFFF"
        focus: true

        ScrollView
        {
            x:0
            y:0
            width: textRect.width
            height: textRect.height

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
                focus: true

                Timer
                {
                    id: cursorTimer
                    interval: 800
                    running: true
                    repeat: true
                    onTriggered:
                    {
                        viewer.cursorVisible = !viewer.cursorVisible;
                        viewer.update();
                    }
                }

                MouseArea
                {
                    x: 0
                    y: 0
                    width: textRect.width
                    height: textRect.height
                    preventStealing: true
                    hoverEnabled: true
                    focus: true
                    onPressed: {
                        if(viewer.document != null)
                        {
                            var val = viewer.getNewSelection(mouseX, mouseY);
                            AppData.cursorPosition = val;
                            viewer.cursorPos = val;
                            viewer.cursorVisible = true;
                            viewer.begindex = -1;
                            viewer.endex = -1;
                            cursorTimer.restart();
                            console.log("press " + val);
                            viewer.update();
                        }
                    }

                    onPositionChanged: {
                        if(pressed && viewer.document != null)
                        {
                            var val = viewer.getNewSelection(mouseX, mouseY);

                            if(val > viewer.cursorPos)
                            {
                                viewer.begindex = viewer.cursorPos;
                                viewer.endex = val;
                            }
                            else if(val < viewer.cursorPos)
                            {
                                viewer.begindex = val;
                                viewer.endex = viewer.cursorPos;
                            }
                            else
                            {
                                viewer.begindex = -1;
                                viewer.endex = -1;
                            }

                            viewer.update();
                            console.log("release" + val);
                        }
                    }
                }
            }
        }

        Keys.onPressed: {
            if(event.key == Qt.Key_Left)
            {
                if(viewer.cursorPos > 0)
                {
                    viewer.cursorPos--;
                }
            }
            else if(event.key == Qt.Key_Right)
            {
            }
            else if(event.key == Qt.Key_Up)
            {

            }
            else if(event.key == Qt.Key_Down)
            {

            }
            else if(event.key == Qt.Key_Backspace)
            {

            }
            else
            {
                if(event.text != "")
                {
                    AppData.insert(AppData.docIndex, viewer.cursorPos, event.text);
                    viewer.cursorPos++;
                }
            }

            viewer.cursorVisible = true;
            cursorTimer.restart();
            viewer.update();
        }
    }
}

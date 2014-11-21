import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import TextViewer 1.0
import Document 1.0

ApplicationWindow {
    id: mainApp
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    Dialog
    {
        id: nameDialog
        visible: false
        title: "Name File"
        standardButtons: StandardButton.Ok
        Rectangle {
            color: "#DDDDDD"
            width: 180
            height: 100
            implicitWidth: width
            implicitHeight: height

            Row
            {
                anchors.centerIn: parent

                Text {
                    text: "Filename: "
                }

                TextField {
                    id: filename
                }
            }
        }

        onAccepted:
        {
            var docIndex = AppData.create_document(filename.text);
            console.log("docIndex = " + docIndex);
            if(docIndex !== -1)
                sidePanel.createDocumentTab(docIndex);
            nameDialog.visible = false;
        }

        onRejected:
        {
            visible = false;
        }
    }

    FileDialog
    {
        id: filePicker
        title: "Please Choose a File"
        selectMultiple: false
        selectFolder: false
        selectExisting: true
        nameFilters: ["Text files: (*.txt , *.c , *.h , *.cpp , *.hpp )", "All files (*)"];

        onAccepted:
        {
            var docIndex = AppData.open_document(fileUrl);
            if(docIndex !== -1)
                sidePanel.createDocumentTab(docIndex);
            filePicker.close()
        }

        onRejected:
        {
            filePicker.close()
        }
    }

    FileDialog
    {
        id: filePickerSave
        title: "Save your file"
        selectMultiple: false
        selectFolder: false
        selectExisting: false
        nameFilters: ["Text files: (*.txt , *.c , *.h , *.cpp , *.hpp )", "All files (*)"];

        onAccepted:
        {
            var theResult = AppData.save_document(fileUrl);
            if(theResult === false)
                console.log("shit");
            filePicker.close()
        }

        onRejected:
        {
            console.log("bad")
            filePicker.close()
        }
    }

    function createDocument()
    {
        nameDialog.visible = true
        viewer.cursorPos = 0;
    }

    function openDocument()
    {
        filePicker.selectExisting = true;
        filePicker.open();
        viewer.cusorPos = 0;
    }

    function saveDocument()
    {
        var doc = AppData.get_document_at(AppData.docIndex);
        if(doc.path !== "")
        {
            var success = AppData.save_document(AppData.docIndex);
            if(success === false)
                filePickerSave.open();
        }
        else
            result = filePickerSave.open();
    }

    function saveasDocument()
    {
        filePickerSave.open();
    }

    function closeDocument()
    {
        sidePanel.deleteDocumentTab(AppData.docIndex);
        AppData.close_document(AppData.docIndex);
    }

    menuBar: MenuBar {
        id: menu
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&New")
                onTriggered:
                {
                    createDocument();
                }
            }
            MenuItem {
                text: qsTr("&Open")
                onTriggered:
                {
                    openDocument();
                }
            }
            MenuItem {
                text: qsTr("&Save")
                onTriggered:
                {
                    saveDocument();
                }
            }
            MenuItem {
                text: qsTr("&Save As...")
                onTriggered:
                {
                    saveasDocument();
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("&Copy")
                onTriggered:
                {
                    if(viewer.begindex != -1 && viewer.endex != -1)
                    {
                        AppData.copy(AppData.docIndex, viewer.begindex, viewer.endex);
                    }
                }
            }
            MenuItem {
                text: qsTr("&Cut")
                onTriggered:
                {
                    if(viewer.begindex != -1 && viewer.endex != -1)
                    {
                        AppData.cut(AppData.docIndex, viewer.begindex, viewer.endex);
                    }
                }
            }
            MenuItem {
                text: qsTr("&Paste")
                onTriggered:
                {
                    var numChar = AppData.paste(AppData.docIndex, viewer.cursorPos);
                    viewer.cursorPos += numChar;
                }
            }
        }
    }

    Sidebar
    {
        id: sidePanel
        onSelectionChanged:
        {
            AppData.docIndex = sidePanel.currentSelection;
            console.log("new index" + AppData.docIndex);
            viewer.cursorPos = 0;
            viewer.document = AppData.get_document_at(AppData.docIndex);
            console.log("updating doc: " + viewer.document);
            viewer.update();
        }
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
                document: null
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
                        viewer.document = AppData.get_document_at(AppData.docIndex);
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
                            console.log("column: " + viewer.currentColumn);
                            AppData.cursorPosition = val;
                            viewer.cursorPos = val;
                            viewer.cursorVisible = true;
                            viewer.begindex = -1;
                            viewer.endex = -1;
                            cursorTimer.restart();
                            viewer.document = AppData.get_document_at(AppData.docIndex);
                            console.log("updating doc: " + viewer.document);
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
                            viewer.document = AppData.get_document_at(AppData.docIndex);
                            console.log("updating doc: " + viewer.document);
                            viewer.update();
                        }
                    }
                }
            }
        }

        Keys.onPressed: {
            var doc = AppData.get_document_at(AppData.docIndex);
            if(doc !== null)
            {
                if(event.key === Qt.Key_Left)
                {
                    if(viewer.cursorPos > 0)
                    {
                        viewer.cursorPos--;
                        console.log("column: " + viewer.currentColumn);
                        AppData.cursorPosition = viewer.cursorPos;
                        viewer.cursorVisible = true;
                        viewer.begindex = -1;
                        viewer.endex = -1;
                        viewer.document = AppData.get_document_at(AppData.docIndex);
                        viewer.update();
                    }
                }
                else if(event.key === Qt.Key_Right)
                {
                    var doc = AppData.get_document_at(AppData.docIndex);
                    if(viewer.cursorPos <= doc.filesize())
                    {
                        console.log("column: " + viewer.currentColumn);
                        viewer.cursorPos++;
                        AppData.cursorPosition = viewer.cursorPos;
                        viewer.cursorVisible = true;
                        viewer.begindex = -1;
                        viewer.endex = -1;
                        cursorTimer.restart();
                        viewer.document = AppData.get_document_at(AppData.docIndex);
                        console.log("updating doc: " + viewer.document);
                        viewer.update();
                    }
                }
                else if(event.key === Qt.Key_Up)
                {
                    if(viewer.currentRow > 0)
                    {
                        var val = viewer.newSelectionFromRowCol(viewer.currentColumn, viewer.currentRow - 1);
                        console.log("column: " + viewer.currentColumn);
                        viewer.cursorPos = val;
                        AppData.cursorPosition = viewer.cursorPos;
                        viewer.cursorVisible = true;
                        viewer.begindex = -1;
                        viewer.endex = -1;
                        cursorTimer.restart();
                        viewer.document = AppData.get_document_at(AppData.docIndex);
                        console.log("updating doc: " + viewer.document);
                        viewer.update();
                    }
                }
                else if(event.key === Qt.Key_Down)
                {
                    var val = viewer.newSelectionFromRowCol(viewer.currentColumn, viewer.currentRow + 1);
                    console.log("column: " + viewer.currentColumn);
                    viewer.cursorPos = val;
                    AppData.cursorPosition = viewer.cursorPos;
                    viewer.cursorVisible = true;
                    viewer.begindex = -1;
                    viewer.endex = -1;
                    cursorTimer.restart();
                    viewer.document = AppData.get_document_at(AppData.docIndex);
                    console.log("updating doc: " + viewer.document);
                    viewer.update();
                }
                else if(event.key === Qt.Key_Backspace)
                {
                    if(viewer.cursorPos > 0)
                    {
                        viewer.cursorPos--;
                        AppData.backspace(AppData.docIndex, viewer.cursorPos);
                    }
                }
                else if(event.key === Qt.Key_Return)
                {
                    AppData.insert(AppData.docIndex, viewer.cursorPos, '\n');
                    viewer.cursorPos++;
                }
                else if(event.key === Qt.Key_C && event.modifiers === Qt.ControlModifier &&
                        viewer.begindex != -1 && viewer.endex != -1)
                {
                    AppData.copy(AppData.docIndex, viewer.begindex, viewer.endex);
                }
                else if(event.key === Qt.Key_V && event.modifiers === Qt.ControlModifier)
                {
                    var numChar = AppData.paste(AppData.docIndex, viewer.cursorPos);
                    viewer.cursorPos += numChar;
                }
                else if(event.key == Qt.Key_X && event.modifiers === Qt.ControlModifier &&
                        viewer.begindex != -1 && viewer.endex != -1)
                {
                    AppData.cut(AppData.docIndex, viewer.begindex, viewer.endex);
                    viewer.begindex = -1;
                    viewer.endex = -1;
                }
                else
                {
                    if(event.text !== "" && event.modifiers !== Qt.ControlModifier)
                    {
                        AppData.insert(AppData.docIndex, viewer.cursorPos, event.text);
                        viewer.cursorPos++;
                    }
                }

                viewer.updateRowCol();
                viewer.cursorVisible = true;
                cursorTimer.restart();
                viewer.document = AppData.get_document_at(AppData.docIndex);
                viewer.update();
            }
        }
    }
}

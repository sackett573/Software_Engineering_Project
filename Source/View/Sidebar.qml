import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: mainRect
    width: 250
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    color: "#AAAAAA"

    Component.onDestruction:
    {
        for(var i = 0; i < documentList.count; i++)
            documentList.get(i).destroy;
    }

    property int currentSelection: -1;

    signal selectionChanged;

    function createDocumentTab(docIndex) {
        var doc = AppData.get_document_at(docIndex);

        var docModel = Qt.createQmlObject(
        "import QtQuick 2.3

        Item {
            property string filename: \"" + doc.filename + "\"
            property int index: " + docIndex + "
        }", mainRect);
        documentList.append(docModel);
    }

    function deleteDocumentTab(docIndex) {
        for(var i = 0; i < documentList.count; i++)
        {
            if(documentList.get(i).index == docIndex)
            {
                documentList.remove(i);
                break;
            }
        }

        for(var i = 0; i < documentList.count; i++)
        {
            if(documentList.get(i).index > docIndex)
                documentList.get(i).index--;
        }
    }

    ListModel
    {
        id: documentList

    }

    Component
    {
        id: listDelegate
        SidebarElement
        {
            width: mainRect.width

            text: filename
            imagePath: "Images/doc_icon.png"
            docIndex: index

            onSelected: {
                currentSelection = docIndex;
                selectionChanged();
            }
        }
    }

    ColumnLayout
    {
        anchors.fill: parent
        Layout.alignment: Qt.AlignTop
        spacing: 0

        ListView {
            id: listView
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.minimumHeight: height
            Layout.preferredHeight: height
            Layout.maximumHeight: mainRect.height - optionRow.height
            anchors.margins: 0

            model: documentList
            delegate: listDelegate

            width: mainRect.width
            height: 80 * documentList.count
            contentHeight: 80 * documentList.count - 50
            contentWidth: mainRect.width - 50

            ScrollView
            {
                anchors.fill: listView
                contentItem: parent
            }
        }

        RowLayout {
            id: optionRow
            anchors.top: listView.bottom
            spacing: 0

            Rectangle
            {
                id: b1
                color: "#CCCCCC"
                width: mainRect.width/3
                height: 80
                border.color: "black"
                anchors.right: b2.left

                Image
                {
                    width: parent.width/2
                    height: parent.height/2
                    x: parent.width/2 - width/2
                    y: parent.height/2 - height/2
                    source: "Images/create_icon.png"
                    smooth: true
                    mipmap: true
                    antialiasing: true
                }

                MouseArea {
                    anchors.fill: parent

                    onPressed: {
                        parent.color = "#999999"
                    }

                    onClicked: {
                        parent.color = "#CCCCCC"
                        createDocument();
                    }
                }
            }

            Rectangle
            {
                id:b2
                color: "#CCCCCC"
                width: mainRect.width/3
                height: 80
                border.color: "black"

                Image
                {
                    width: parent.width/2
                    height: parent.height/2
                    x: parent.width/2 - width/2
                    y: parent.height/2 - height/2
                    source: "Images/open_icon.png"
                    smooth: true
                    mipmap: true
                    antialiasing: true
                }

                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        parent.color = "#999999"
                    }

                    onClicked: {
                        openDocument();
                        parent.color = "#CCCCCC"
                    }
                }
            }

            Rectangle
            {
                id:b3
                color: "#CCCCCC"
                width: mainRect.width/3
                height: 80
                border.color: "black"

                anchors.left: b2.right

                Image
                {
                    width: parent.width/2
                    height: parent.height/2
                    x: parent.width/2 - width/2
                    y: parent.height/2 - height/2
                    source: "Images/close_icon.png"
                    smooth: true
                    mipmap: true
                    antialiasing: true
                }

                MouseArea {
                    anchors.fill: parent

                    onPressed: {
                        parent.color = "#999999"
                    }

                    onClicked: {
                        parent.color = "#CCCCCC"
                        closeDocument();
                    }
                }
            }
        }
    }
}

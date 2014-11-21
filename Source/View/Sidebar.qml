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
            color: mainRect.color
            text: "test"
            imagePath: "Images/doc_icon.png"
        }
    }

    ColumnLayout
    {
        anchors.fill: parent

        Item
        {
            x: 0
            y: 0
            width: documentList.count * 80
            height: view.height
            Layout.alignment: Qt.AlignTop

            ListView {
                id: view
                anchors.fill: parent
                model: documentList
                delegate: listDelegate
            }
        }

        Row {
            Layout.alignment: Qt.AlignTop
            width: mainRect.width
            height: 80


            Rectangle
            {
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

                    onReleased: {
                        parent.color = "#CCCCCC"
                    }
                }
            }

            Rectangle
            {
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

                    onReleased: {
                        parent.color = "#CCCCCC"
                    }
                }
            }

            Rectangle
            {
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

                    onReleased: {
                        parent.color = "#CCCCCC"
                    }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onPressed: {
            var meh = Qt.createQmlObject(
"import QtQuick 2.3

Item {
    property string filename: \"empty\"
    property int index: -1
}", mainRect);
            documentList.append(meh);

            console.out("listSize: " + documentList.count);
        }
    }
}

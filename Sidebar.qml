import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    width: 300
    color: "#AAAAAA"
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom

    Component {
        id: documentDelegate
        Item {

        }
    }

    ListView {
        anchors.top : parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        model: DocumentData
        delegate: documentDelegate
        focus: true
    }
}

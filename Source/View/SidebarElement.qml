import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Rectangle {
    id: tabRect
    height: 80
    color: "#AAAAAA"
    border.color: "#000000"
    Layout.minimumWidth: width
    Layout.minimumHeight: height

    property int docIndex: -1
    property string text: "<error>"
    property string imagePath: "<error>"
    property bool isSelected: false

    signal selected(var docIndex);

    function unselect(){
        console.log("wakka");
        tabRect.color = "#AAAAAA";
        overlay.color = "#000000"
        tabText.color = "black"
        textRect.color = "#AAAAAA"
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            isSelected = true;
            selected(docIndex);

            parent.color = "#888888"
            overlay.color = "#FFFFFF"
            tabText.color = "#FFFFFF"
            textRect.color = "#888888"
        }

        onReleased: {
            unselect();
        }
    }

    RowLayout {
        anchors.fill: parent

        Image {
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.preferredWidth: 50
            Layout.preferredHeight: 50
            source: imagePath

            sourceSize.width: parent.height
            sourceSize.height: parent.height
            smooth: true
            mipmap: true
            antialiasing: true


            ColorOverlay {
                id: overlay
                anchors.fill: parent
                source: parent
                color: "#000000"
            }

        }

        Item
        {

            Layout.fillWidth: true
            Layout.minimumHeight: parent.height
            Layout.minimumWidth:  parent.height
            Layout.preferredHeight: parent.height

            Rectangle {
                id: textRect
                color: tabRect.color
                anchors.fill: parent
                anchors.margins: 1

                Text {
                    id: tabText
                    anchors.left: parent.left
                    anchors.leftMargin: parent.height/6
                    anchors.verticalCenter: parent.verticalCenter

                    font.family: "Arial"
                    font.pointSize: 11
                    font.weight: Font.Light
                    font.letterSpacing: 1
                    color: "black"

                    text: tabRect.text
                }
            }
        }
    }
}

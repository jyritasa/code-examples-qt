import QtQuick 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15



Drawer {
    width: 0.66 * parent.width
    height: parent.height

    edge: "LeftEdge"

    ListView {
        anchors.fill: parent;
        model: _myModel

        delegate: Rectangle {
            color: Qt.rgba(0.9,0.9,0.9)
            height: 20
            width: parent.width
            RowLayout{
                width: parent.width
                height: childrenRect.height
                spacing: 0
                Rectangle{
                    Layout.fillWidth: true
                    Text {
                        anchors.fill: parent
                        font.pixelSize: 16
                        text: model.name
                    }
                }
                Rectangle{
                    Layout.fillWidth: true
                    Text {
                        anchors.fill: parent
                        font.pixelSize: 16
                        text: model.score
                    }
                }
                Rectangle{
                    Layout.fillWidth: true
                    Text {
                        anchors.fill: parent
                        font.pixelSize: 16
                        text: model.date
                    }
                }
            }
        }
    }
}

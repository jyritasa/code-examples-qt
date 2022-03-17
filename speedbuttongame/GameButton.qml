import QtQuick 2.0

Rectangle{
    property string buttonColorOn:  "red"
    property int buttonNumber: 0
    color: (_backend.m_nextButton === buttonNumber)? buttonColorOn : Qt.darker(buttonColorOn)
    width: parent.width/4
    height: width
    radius: 100
    MouseArea{
        anchors.fill: parent
        onClicked: {
            _backend.buttonPress(buttonNumber)
        }
    }
}

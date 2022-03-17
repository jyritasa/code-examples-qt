import QtQuick 2.0

Row{

    width: parent.width
    height: parent.height*0.5

    Text {
        anchors.fill: parent
        fontSizeMode: Text.Fit
        font.pixelSize: 10000 // maximum height of the font
        minimumPixelSize: 8 // minimum height of the font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: (_backend.m_score < 10) ? "0"+_backend.m_score : _backend.m_score
    }
}

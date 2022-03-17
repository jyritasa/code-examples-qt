import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.1

Dialog{
    id: gameoverdialog
    width: parent.width
    height: parent.height
    visible: (_backend.m_gameOver);
    modal: true
    Column{
        anchors.fill: parent
        width: parent.width
        Control{
            padding: 10
            contentItem: Row{
                Text {
                    id: name
                    text: "Your Score Was: " + _backend.m_score
                    font.pixelSize: 22
                }
            }
        }
        Control{
            padding: 10
            contentItem: Row{
                spacing: 25
                Label{
                    font.pixelSize: 22
                    text: "Name:"
                }

                TextField {
                    id: nameInput
                    font.pixelSize: 18
                }
            }
        }
        Control{
            padding: 10
            contentItem: Row{
                width: parent.width
                spacing: 5;

                Button{
                    text: "Submit"
                    onClicked: {
                        _myModel.submitScore(nameInput.text, _backend.m_score)
                        _backend.gameOver = false
                        //reset score to 0 after dialog is closed
                        _backend.m_score = 0
                        _backend.scoreChanged()
                        _backend.startGame()
                        gameoverdialog.close()
                        drawer.open()
                    }
                }
                Button{
                    text: "Close"
                    onClicked: {
                        _backend.gameOver = false
                        //reset score to 0 after dialog is closed
                        _backend.m_score = 0
                        _backend.scoreChanged()
                        _backend.startGame()
                        gameoverdialog.close()
                    }
                }
            }
        }
    }
}

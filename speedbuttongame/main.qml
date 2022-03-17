import QtQuick 2.2
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Speden Speed Peli")

    GameOverDialog{
        id: gameoverdialog
    }

    GameStartDialog{
        id: startdialog
    }

    ScoreDrawer{
        id: drawer
    }

    Column{
        width: parent.width
        height: parent.height

        ScoreScreenRow{
            id: scoreRow
        }
        Row{
            id: buttonRow
            width: parent.width
            height: parent.height*0.5

            GameButton{
                //Red
                buttonColorOn: "#FF0000"
                buttonNumber: 1
            }

            GameButton{
                //Yellow
                buttonColorOn: "#F9FF00"
                buttonNumber: 2
            }

            GameButton{
                //Green
                buttonColorOn: "#1FEE0B"
                buttonNumber: 3
            }

            GameButton{
                //Orange
                buttonColorOn: "#FF9C00"
                buttonNumber: 4
            }
        }
    }
}

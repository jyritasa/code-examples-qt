import QtQuick 2.2
import QtQuick.Dialogs 1.1

MessageDialog {
    title: "WECLOME!"
    text: "Press To Start Game."
    onAccepted: {
        _backend.startGame()
        this.close()
    }
    Component.onCompleted: visible = true
}

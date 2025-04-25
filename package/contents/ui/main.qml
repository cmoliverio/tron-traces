import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    width: 1920
    height: 1080

    Text {
        anchors.centerIn: parent
        text: Gol.helloWorld()
        font.pixelSize: 48
        color: "white"
    }
}
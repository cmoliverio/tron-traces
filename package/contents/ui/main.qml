import QtQuick
import QtQuick.Layouts
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.wallpapers.tron_traces 1.0

Rectangle {
    id: root
    color: "black"
    
    TRONTraces {
        id: tronTraces
    }
    
    Text {
        anchors.centerIn: parent
        text: tronTraces.helloWorld()
        color: "white"
        font.pixelSize: 24
    }
}
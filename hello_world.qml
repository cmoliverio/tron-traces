// import QtQuick 2.14
// 
// Rectangle {
//     id: page
//     width: 320; height: 480
//     color: "lightgray"
// 
//     Text {
//         id: helloText
//         text: "Hello world!"
//         y: 30
//         anchors.horizontalCenter: page.horizontalCenter
//         font.pointSize: 24; font.bold: true
//     }
// }

import QtQuick 
import QtQuick.Layouts
import org.kde.plasma.plasmoid
import org.kde.plasma.core as PlasmaCore

WallpaperItem {
    id: root

    Canvas {
        id: gameCanvas
        anchors.fill: parent
        property int mleft: 0
        property int mtop: 0
        width: parent.width
        height: parent.height
    }
}



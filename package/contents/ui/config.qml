import QtQuick 2.12
import QtQuick.Layouts 1
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import Qt.labs.folderlistmodel 2
import "./Components"

import org.kde.plasma.core 2.0 as PlasmaCore

Item {

    ColumnLayout {
    spacing: units.largeSpacing
    Layout.fillWidth: true

    Label {
      width:100
      text: i18n("Pause:")
    }

    RowLayout{

      ImageBtn {
          width: 32
          height: 32
          imageUrl: isPaused ?  "./Resources/play.svg" : "./Resources/pause.svg"
          tipText: isPaused ? "Resume" : "Pause"
          property bool isPaused: false
          onClicked: {
              wallpaper.configuration.running = isPaused
              isPaused = !isPaused;
          }
          Rectangle {
              anchors.fill: parent
              color: "transparent"
              border.width: parent.containsMouse ? 1 : 0
              border.color: "gray"
          }
      }

      Text {
          text: wallpaper.configuration.running ? fpsItem.fps + " fps" : "stopped"
          color: "white"
          anchors.verticalCenter: parent.verticalCenter
      }

    }
  }
}
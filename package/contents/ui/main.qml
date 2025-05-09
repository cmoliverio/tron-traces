import QtQuick 2.15

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.wallpapers.image 2.0 as Wallpaper
import org.kde.plasma.plasmoid

import org.kde.plasma.wallpapers.tron_traces 1.0

WallpaperItem {
    id: root
    anchors.fill: parent

    TronTracesItem {
        anchors.fill: parent
    }
}

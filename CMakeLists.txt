cmake_minimum_required(VERSION 3.16)
project(plasma-wallpaper-gol)

set(CMAKE_CXX_STANDARD 17)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)
find_package(KF6 REQUIRED COMPONENTS Plasma)

add_subdirectory(src)

install(DIRECTORY package/ DESTINATION ${KDE_INSTALL_DATADIR}/plasma/wallpapers/trontraces)
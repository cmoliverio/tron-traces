cmake_minimum_required(VERSION 3.16)
project(plasma-wallpaper-tron-traces)

set(CMAKE_CXX_STANDARD 17)

set(QT_MIN_VERSION "6.4.0")
set(KF6_MIN_VERSION "6.0.0")

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED
    Core
    Qml
    Quick
)

find_package(KF6 COMPONENTS
    Config
    CoreAddons
    WindowSystem
    REQUIRED
)

find_package(Plasma REQUIRED)
find_package(PlasmaQuick REQUIRED)

add_subdirectory(src)

install(DIRECTORY package/ DESTINATION ${PLASMA_DATA_INSTALL_DIR}/wallpapers/org.kde.plasma.tron_traces)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
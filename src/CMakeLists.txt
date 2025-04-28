add_library(libtron_traces MODULE
    tron_traces.cpp
)

target_link_libraries(libtron_traces
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    KF6::ConfigCore
    KF6::CoreAddons
    KF6::WindowSystem
    Plasma
    PlasmaQuick
)

set_target_properties(libtron_traces PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/package/contents/
)

install(TARGETS libtron_traces DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/wallpapers/tron_traces)
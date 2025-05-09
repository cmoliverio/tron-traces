add_library(libtron_traces SHARED MODULE
    tron_traces_renderer.cpp
    tron_traces.cpp
    tron_traces_plugin.cpp
)

target_include_directories(libtron_traces 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(libtron_traces
    PUBLIC
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
        KF6::ConfigCore
        KF6::CoreAddons
        KF6::WindowSystem
        Plasma
        PlasmaQuick
    PRIVATE 
        OpenGL::GL 
        OpenGL::GLU
)

set_target_properties(libtron_traces PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

set(INSTALL_DIR /usr/lib/qt6/qml/org/kde/plasma/wallpapers/tron_traces)

# install the lib
install(
    TARGETS 
        libtron_traces 
    DESTINATION 
        ${INSTALL_DIR}
)

# install the other Qt files needed
install(
    FILES 
        tron_traces.json 
        qmldir 
    DESTINATION 
        ${INSTALL_DIR}
)
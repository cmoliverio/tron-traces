set(MOC_HEADERS
    ${CMAKE_SOURCE_DIR}/include/tron_traces.hpp
    ${CMAKE_SOURCE_DIR}/include/tron_traces_renderer.hpp
    ${CMAKE_SOURCE_DIR}/include/tron_traces_plugin.hpp
)

qt6_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_library(libtron_traces MODULE
    tron_traces_plugin.cpp
    tron_traces.cpp
    tron_traces_renderer.cpp
    ${MOC_SOURCES}
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
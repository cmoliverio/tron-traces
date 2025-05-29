set(MOC_HEADERS
    ${CMAKE_SOURCE_DIR}/include/tron_traces_plugin.hpp
    ${CMAKE_SOURCE_DIR}/include/tron_traces.hpp
    ${CMAKE_SOURCE_DIR}/include/plugin_renderer.hpp
    ${CMAKE_SOURCE_DIR}/include/the_grid.hpp
)

qt6_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_library(libtron_traces MODULE
    tron_traces_plugin.cpp
    tron_traces.cpp
    plugin_renderer.cpp
    the_grid.cpp
    ${MOC_SOURCES}
)

target_include_directories(libtron_traces 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(libtron_traces
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    KF6::ConfigCore
    KF6::CoreAddons
    KF6::WindowSystem
    Plasma
    PlasmaQuick
    # PRIVATE 
    #     OpenGL::GL 
    #     OpenGL::GLU
        # GLEW::GLEW
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
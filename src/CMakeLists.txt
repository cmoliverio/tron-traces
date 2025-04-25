add_library(plasma_wallpaper_tron_traces MODULE
    tron_traces.cpp
)

target_link_libraries(plasma_wallpaper_tron_traces
    Qt::Core
    Qt::Quick
    Qt:Qml
    KF6::ConfigCore
    KF6::CoreAddons
    KF6::WindowSystem
)

set_target_properties(plasma_wallpaper_tron_traces PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/package/contents/
)
add_library(plasma_wallpaper_tron_traces MODULE
    tron_traces.cpp
)

target_link_libraries(plasma_wallpaper_tron_traces
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    KF6::Plasma
)

set_target_properties(plasma_wallpaper_tron_traces PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/package/contents/
)
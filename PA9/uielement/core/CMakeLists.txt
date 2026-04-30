add_library(core
    ui_manager.cpp
)

target_include_directories(core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
    PUBLIC
    SFML::Graphics
)
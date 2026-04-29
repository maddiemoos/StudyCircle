add_library(menu menu.cpp)

target_include_directories(menu
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(menu PUBLIC
    SFML::Graphics
)
add_library(uielement uielement.cpp)

target_include_directories(uielement
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(menu PUBLIC
    SFML::Graphics
)
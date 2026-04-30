# We want to propergate the parent class, so it'll be a header only
add_library(uielement INTERFACE)

target_include_directories(uielement
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(uielement
    INTERFACE
    SFML::Graphics
)
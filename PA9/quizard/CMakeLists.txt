add_library(quizard
    quizard.cpp
)

target_include_directories(quizard
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(quizard PUBLIC
    SFML::Graphics
)
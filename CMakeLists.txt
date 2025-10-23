cmake_minimum_required(VERSION 3.23)

# set project name and language
project(SFML_CHESS LANGUAGES CXX)

# set C++ language version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# include FetchContent module to fetch external libraries
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

# add subdirectories
add_subdirectory("src/game_logic")
# add_subdirectory("src/game_render")

# add executables to (the program)
add_executable(main "src/main.cpp")

# add custom target for copying assets
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:main>/assets"
)

# add dependecies
add_dependencies(main copy_assets)


# link dependencies and libraries
target_link_libraries(main
    PRIVATE
        GameLogic
        # GameRender
        SFML::Graphics
        SFML::Window
        SFML::System
)
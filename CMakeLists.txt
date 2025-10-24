cmake_minimum_required(VERSION 3.23)

# Set project name and language
project(SFML_CHESS LANGUAGES CXX)

# Set C++ language version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include FetchContent module to fetch external libraries
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

# Add subdirectories
add_subdirectory("src/game_logic")
# Add_subdirectory("src/game_render")

# Add executables to (the program)
add_executable(main "src/main.cpp")

# Add custom target for copying assets
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:main>/assets"
)

# Add dependecies
add_dependencies(main copy_assets)


# Link dependencies and libraries
target_link_libraries(main
    PRIVATE
        GameLogic
        # GameRender
        SFML::Graphics
        SFML::Window
        SFML::System
)
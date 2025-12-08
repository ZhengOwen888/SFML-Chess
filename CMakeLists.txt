cmake_minimum_required(VERSION 3.23)

# Set project name and language
project(SFML_CHESS LANGUAGES CXX)

# Set C++ language version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set variables
set(ENGINE_DIR "${CMAKE_SOURCE_DIR}/stockfish_engine")
set(BUILD_DIR "$<TARGET_FILE_DIR:main>")

# Include FetchContent module to fetch external libraries
include(FetchContent)

set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    GIT_REPOSITORY "https://github.com/boostorg/boost.git"
    GIT_TAG "boost-1.84.0"
)
FetchContent_MakeAvailable(Boost)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "3.0.2"
)
FetchContent_MakeAvailable(SFML)


# Add subdirectories
add_subdirectory("src/game_logic")
add_subdirectory("src/game_render")
add_subdirectory("src/chess_app")

# Add executables to (the program)
add_executable(main "src/main.cpp")

if(WIN32)
    set(SF_EXEC_SRC "${ENGINE_DIR}/stockfish_AVX2/stockfish-ubuntu-x86-64-avx2")
elseif(APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(SF_EXEC_SRC "${ENGINE_DIR}/stockfish_AppleSilicon/stockfish-macros-m1-apple-silicon")
    elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(SF_EXEC_SRC "${ENGINE_DIR}/stockfish_BMI2/stockfish-macos-x86-64-bmi2")
    else()
        message(FATAL_ERROR "Unsupported MAC architexture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
elseif(UNIX)
    set(SF_EXEC_SRC "${ENGINE_DIR}/stockfish_AVX2/stockfish-ubuntu-x86-64-avx2")
else()
    message(FATAL_ERROR "Unsupported operating system.")
endif()

set(ENGINE_NAME "stockfish")
set(ENGINE_PATH "./${ENGINE_NAME}")
set(SF_EXEC_DEST "${BUILD_DIR}/${ENGINE_NAME}")

# Add custom command for copying the stockfish engine UCI
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SF_EXEC_SRC}"
        "${SF_EXEC_DEST}"
    COMMENT "Copying stockfish engine executable to build directory"
)

# Add custom command for copying assets
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${BUILD_DIR}/assets"
    COMMENT "Copying assets to build directory"
)

# Link dependencies and libraries
target_link_libraries(main
    PRIVATE
        GameLogic
        GameRender
        ChessApp
        SFML::Graphics
        SFML::Window
        SFML::System
        Boost::process
        Boost::asio
        Boost::system
)
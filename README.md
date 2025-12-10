# SFML Chess Game

A simple chess game built using **C++** and **SFML**.
It features smooth board and piece rendering, full chess logic, and integration with the **Stockfish** engine, enabling single-player gameplay against a computer opponent.

## Build Instructions

### Prerequisites

Make sure to have CMake downloaded in order to build the project.

### Linux / macOS

Download the zip file and open the terminal:

```bash
cd /path/to/SFML-Chess
mkdir build
cd build
cmake ..
make
./main
```

### Windows

If you are using MinGW download the zip file and open the terminal:

```bash
cd /path/to/SFML-Chess
mkdir build
cd build
cmake ..
make
./main
```

## File Structure

```bash
.
├── assets
│   ├── boards/
│   │   ├── classic/
│   │   │   └── board.png
│   │   ├── ocean/
│   │   │   └── board.png
│   │   └── walnut/
│   │       └── board.png
│   ├── fonts/
│   │   └── *.ttf
│   └── pieces/
│       ├── classic/
│       │   ├── dark
│       │   │   └── *.png
│       │   └── light
│       │       └── *.png
│       ├── ocean/
│       │   ├── dark
│       │   │   └── *.png
│       │   └── light
│       │       └── *.png
│       └── walnut/
│           ├── dark
│           │   └── *.png
│           └── light
│               └── *.png
├── include
│   ├── chess_app/
│   │   ├── game_manager.hpp
│   │   └── uci_handler.hpp
│   ├── game_logic/
│   │   ├── base/
│   │   │   └── *.hpp
│   │   ├── pieces/
│   │   │   └── *.hpp
│   │   ├── validator/
│   │   │   └── *validator.hpp
│   │   ├── constants.hpp
│   │   ├── enums.hpp
│   │   └── game.hpp
│   └── game_render/
│       ├── manager/
│       │   └── *manager.hpp
│       ├── renderer/
│       │   └── *renderer.hpp
│       ├── constants.hpp
│       └── enums.hpp
├── src
│   ├── chess_app/
│   │   ├── game_manager.cpp
│   │   ├── uci_handler.cpp
│   │   └── CMakeLists.txt
│   ├── game_logic/
│   │   ├── base/
│   │   │   └── *.cpp
│   │   ├── pieces/
│   │   │   └── *.cpp
│   │   ├── validator/
│   │   │   └── *validator.cpp
│   │   ├── game.cpp
│   │   └── CMakeLists.txt
│   ├── game_render/
│   │   ├── manager/
│   │   │   └── *.cpp
│   │   ├── renderer/
│   │   │   └── *renderer.cpp
│   │   └── CMakeLists.txt
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

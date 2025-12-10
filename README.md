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
├── CMakeLists.txt
├── README.md
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
│   │
│   ├── game_logic/
│   │   ├── base/
│   │   │   └── *.hpp
│   │   │
│   │   ├── pieces/
│   │   │   └── *.hpp
│   │   │
│   │   ├── validator/
│   │   │   └── move_validator.hpp
│   │   │
│   │   ├── constants.hpp
│   │   ├── enums.hpp
│   │   └── game.hpp
│   │
│   └── game_render/
│       ├── constants.hpp
│       ├── enums.hpp
│       ├── manager/
│       │   └── asset_manager.hpp
│       │
│       └── renderer/
│           └── *renderer.hpp
└── src
    ├── chess_app/
    │   ├── CMakeLists.txt
    │   ├── game_manager.cpp
    │   └── uci_handler.cpp
    ├── game_logic/
    │   ├── CMakeLists.txt
    │   ├── base/
    │   │   └── *.cpp
    │   ├── pieces/
    │   │   └── *.cpp
    │   ├── validator/
    │   │   └── move_validator.cpp
    │   └── game.cpp
    ├── game_render/
    │   ├── CMakeLists.txt
    │   ├── manager/
    │   │   └── asset_manager.cpp
    │   └── renderer/
    │       └── *renderer.cpp
    └── main.cpp
```

#ifndef GAMELOGIC_TYPES_HPP
#define GAMELOGIC_TYPES_HPP

#include <array>
#include <utility>
#include <memory>

namespace GameLogic
{
    // Board size (8x8)
    constexpr int BOARD_SIZE = 8;

    // Type alias for representating a position on board (row, col)
    using Position = std::pair<int, int>;

    // Enum class for color of chess pieces, players, and square on board
    enum class Color
    {
        DARK,
        LIGHT,
        NONE
    };

    // Enum for type of the chess pieces
    enum class PieceType
    {
        // piece types here
    };

    // Enum for the direction a piece can move
    enum class Direction
    {
        // directions here
    };

    // Enum for the type of the move
    enum class MoveType
    {
        // move types here
    };
}

#endif
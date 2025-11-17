#ifndef GAMELOGIC_CONSTANTS_HPP
#define GAMELOGIC_CONSTANTS_HPP

namespace GameLogic
{
    namespace Constants
    {
        constexpr int BOARD_SIZE = 8; // 8x8 board
        constexpr int FILE = 8;       // FILE represents the column of the board
        constexpr int RANK = 8;       // RANK represent the row of the board

        // Distance from king to rook
        constexpr int KING_SIDE_ROOK_OFFSET = 3;
        constexpr int QUEEN_SIDE_ROOK_OFFSET = 4;

        // How far the king moves while castling
        constexpr int KING_CASTLE_MOVE_OFFSET = 2;

        // Number of expty squares required between king and rook
        constexpr int KING_SIDE_EMPTY_COUNT = 2;
        constexpr int QUEEN_SIDE_EMPTY_COUNT = 3;

    } // namespace Constants

} // namespace GameLogic

#endif
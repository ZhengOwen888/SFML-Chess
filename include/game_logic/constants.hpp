#ifndef GAMELOGIC_CONSTANTS_HPP
#define GAMELOGIC_CONSTANTS_HPP

#include "game_logic/enums.hpp"

namespace GameLogic
{
    namespace Constants
    {
        inline constexpr int BOARD_SIZE = 8; // 8x8 board
        inline constexpr int FILE = 8;       // FILE represents the column of the board
        inline constexpr int RANK = 8;       // RANK represent the row of the board

        // Distance from king to rook
        inline constexpr int KING_SIDE_ROOK_OFFSET = 3;
        inline constexpr int QUEEN_SIDE_ROOK_OFFSET = 4;

        // How far the king moves while castling
        inline constexpr int KING_CASTLE_MOVE_OFFSET = 2;

        // Number of expty squares required between king and rook
        inline constexpr int KING_SIDE_EMPTY_COUNT = 2;
        inline constexpr int QUEEN_SIDE_EMPTY_COUNT = 3;

        inline constexpr std::array<Enums::Color, 2> AllColors =
        {
            Enums::Color::Light,
            Enums::Color::Dark
        };

        inline constexpr std::array<Enums::PieceType, 6> AllPieceType =
        {
            Enums::PieceType::Pawn,
            Enums::PieceType::Bishop,
            Enums::PieceType::Knight,
            Enums::PieceType::Rook,
            Enums::PieceType::Queen,
            Enums::PieceType::King
        };

    } // namespace Constants

} // namespace GameLogic

#endif
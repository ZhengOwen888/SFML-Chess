#ifndef GAMELOGIC_CONSTANTS_HPP
#define GAMELOGIC_CONSTANTS_HPP

#include "game_logic/enums.hpp"

#include <array>

namespace GameLogic
{
    namespace Constants
    {
        /** @brief The standard size of one dimension of a chess board - 8. */
        inline constexpr int BOARD_SIZE = 8;

        /** @brief The Number of columns on a standard board. */
        inline constexpr int FILE = 8;

        /** @brief The Number of rows on a standard board. */
        inline constexpr int RANK = 8;

        // -- Castling Offsets -- //

        /** @brief The column distance from the king's start position to the king side rooks start position. */
        inline constexpr int KING_SIDE_ROOK_OFFSET = 3;

        /** @brief The column distance from the king's start position to the queen side rooks start position. */
        inline constexpr int QUEEN_SIDE_ROOK_OFFSET = 4;

        /** @brief The number of columns the king moves toward the rooks during castling. */
        inline constexpr int KING_CASTLE_MOVE_OFFSET = 2;

        /** @brief The number of empty columns between the King and the King side rook. */
        inline constexpr int KING_SIDE_EMPTY_COUNT = 2;

        /** @brief The number of empty columns between the King and the Queen side rook. */
        inline constexpr int QUEEN_SIDE_EMPTY_COUNT = 3;

        // -- Collection of Enums -- //

        /** @brief Possible sides or colors of the game. */
        inline constexpr std::array<Enums::Color, 2> AllColors =
        {
            Enums::Color::Light,
            Enums::Color::Dark
        };

        /** @brief All The piece types used in the standard game. */
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
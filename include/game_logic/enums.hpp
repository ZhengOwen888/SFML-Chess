#ifndef GAMELOGIC_ENUMS_HPP
#define GAMELOGIC_ENUMS_HPP

namespace GameLogic
{
    namespace Enums
    {
        /** @brief The possible colors for the game. */
        enum class Color
        {
            None,
            Dark,
            Light,
        };

        /** @brief The type of pieces used. */
        enum class PieceType
        {
            None,
            Pawn,
            Knight,
            Bishop,
            Rook,
            Queen,
            King,
        };

        /** @brief The types of moves. */
        enum class MoveType
        {
            None,
            Normal,     // Normal Moves and Capture
            CastleKS,   // Castling king side
            CastleQS,   // Castling queen side
            DoublePawn, // Pawn moving foward 2 squares as their first move
            EnPassant,  // Pawn capture an opponent's pawn that has just moved two squares from its start position and landed beside it
            PawnPromotion,
        };

        /** @brief The possible game states. */
        enum class GameState
        {
            Ongoing,
            Checkmate,
            Stalemate,           // (draw) not in check, but no legal moves
            ThreeFoldRepetition, // (draw) same position repeated 3 times
            FiftyMoveRule,       // (draw) no pawn move or capture for 50 moves
            InsufficientMaterial,// (draw) niether player has enough pieces to give the other a checkmate
        };
    }
}

#endif
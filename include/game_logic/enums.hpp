#ifndef GAMELOGIC_ENUMS_HPP
#define GAMELOGIC_ENUMS_HPP

#include <array>

namespace GameLogic
{
    namespace Enums
    {
        enum class Color
        {
            Dark,
            Light,
            None
        };

        enum class PieceType
        {
            Pawn,
            Knight,
            Bishop,
            Rook,
            Queen,
            King,
            None
        };

        enum class MoveType
        {
            Normal,     // Normal Moves and Capture
            CastleKS,   // Castling king side
            CastleQS,   // Castling queen side
            DoublePawn, // Pawn moving foward 2 squares as their first move
            EnPassant,  // Pawn capture an opponent's pawn that has just moved two squares from its start position and landed beside it
            PawnPromotion,
            None
        };

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
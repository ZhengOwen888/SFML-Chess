#ifndef GAMELOGIC_ENUMS_HPP
#define GAMELOGIC_ENUMS_HPP

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
            Normal,
            Capture,
            CastleKS,   // castling king side
            CastleQS,   // castling queen side
            DoublePawn, // pawn moving foward 2 squares as their first move
            EnPassant,  // pawn capture an opponent's pawn that has just moved two squares from its start position and landed beside it
            PawnPromotion,
        };

        enum class GameState
        {
            Ongoing,
            Check,
            Checkmate,
            Draw,                // general draw - could be Stalemate, ThreeFoldRepetition ...
            Stalemate,           // (draw) not in check, but no legal moves
            ThreeFoldRepetition, // (draw) same position repeated 3 times
            FiftyMoveRule,       // (draw) no pawn move or capture for 50 moves
            WhiteWin,
            BlackWin
        };
    }
}

#endif
#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include <memory>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Pawn: public Piece
    {
        public:
            // Constructors and destructor
            Pawn(Enums::Color color);
            Pawn(Enums::Color color, bool has_moved, bool has_promoted);
            ~Pawn() = default;

            // Make a clone of this pawn
            std::unique_ptr<Piece> clonePiece() const override;

            // Getter for Pawn type
            Enums::PieceType getPieceType() const override;
    };
}

#endif


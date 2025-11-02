#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include <memory>
#include <vector>
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
            ~Pawn() override = default;

            // Make a clone of this pawn
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a pawn from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
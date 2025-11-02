#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include <memory>
#include <vector>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Knight: public Piece
    {
        public:
            // Constructors and destructor
            Knight(Enums::Color color);
            Knight(Enums::Color color, bool has_moved, bool has_promoted);
            ~Knight() override = default;

            // Clone this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a knight from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
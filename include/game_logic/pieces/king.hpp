#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include <memory>
#include <vector>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class King: public Piece
    {
        public:
            // Constructors and destructor
            King(Enums::Color color);
            King(Enums::Color color, bool has_moved, bool has_promoted);
            ~King() override = default;

            // Clone this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a king from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
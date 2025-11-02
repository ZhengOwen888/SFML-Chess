#ifndef GAMELOGIC_QUEEN_HPP
#define GAMELOGIC_QUEEN_HPP

#include <memory>
#include <vector>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Queen: public Piece
    {
        public:
            // Constructors and destructor
            Queen(Enums::Color color);
            Queen(Enums::Color color, bool has_moved, bool has_promoted);
            ~Queen() override = default;

            // Clone this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a queen from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
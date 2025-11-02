#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include <memory>
#include <vector>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // Constructors and destructor
            Bishop(Enums::Color color);
            Bishop(Enums::Color color, bool has_moved, bool has_promoted);
            ~Bishop() override = default;

            // Clone this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a bishop from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
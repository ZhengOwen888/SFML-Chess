#ifndef GAMELOGIC_ROOK_HPP
#define GAMELOGIC_ROOK_HPP

#include <memory>
#include <vector>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Rook: public Piece
    {
        public:
            // Constructors and destructor
            Rook(Enums::Color color);
            Rook(Enums::Color color, bool has_moved, bool has_promoted);
            ~Rook() override = default;

            // Clone this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get all legal moves for a rook from a given position
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // construct Bishop object with color
            Bishop(Enums::Color color);
            ~Bishop() override;

            // Clone this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get all legal moves for a bishop from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
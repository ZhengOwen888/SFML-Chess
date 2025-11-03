#ifndef GAMELOGIC_QUEEN_HPP
#define GAMELOGIC_QUEEN_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Queen: public Piece
    {
        public:
            // construct a Queen object with color
            Queen(Enums::Color color);
            ~Queen() override;

            // clone this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // get all legal moves for a Queen from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
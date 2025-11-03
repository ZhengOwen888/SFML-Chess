#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Knight: public Piece
    {
        public:
            // construct a Knight object with color
            Knight(Enums::Color color);
            ~Knight() override;

            // clone this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // get all legal moves for a Knight from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class King: public Piece
    {
        public:
            // construct a King object with color
            King(Enums::Color color);
            ~King() override;

            // clone this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // get all legal moves for a King from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
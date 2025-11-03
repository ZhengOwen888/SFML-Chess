#ifndef GAMELOGIC_ROOK_HPP
#define GAMELOGIC_ROOK_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Rook: public Piece
    {
        public:
            // construct a Rook object with color
            Rook(Enums::Color color);
            ~Rook() override;

            // clone this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // get all legal moves for a Rook from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
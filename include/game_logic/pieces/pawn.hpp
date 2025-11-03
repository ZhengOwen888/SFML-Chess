#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Pawn: public Piece
    {
        public:
            // construct a Pawn object with color
            Pawn(Enums::Color color);
            ~Pawn() override = default;

            // clone of this pawn
            std::unique_ptr<Piece> ClonePiece() const override;

            // get all legal moves for a Pawn from a given position
            std::vector<Move> GetLegalMoves(const Position& from_position, Board &board) const;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include <memory>
#include <vector>
#include <array>

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


            // Make a copy of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get knight moves from a square
            // For each jump target: if on board and not friendly piece, include.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

            // Knight jump directions (8 L-shapes)
            static inline const std::array<Direction, 8>& JumpDirs()
            {
                static const std::array<Direction, 8> dirs = {
                    Direction(-2, -1), Direction(-2, +1),
                    Direction(-1, -2), Direction(-1, +2),
                    Direction(+1, -2), Direction(+1, +2),
                    Direction(+2, -1), Direction(+2, +1)
                };
                return dirs;
            }
    };
} // namespace GameLogic

#endif
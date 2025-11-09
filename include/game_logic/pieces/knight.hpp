#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include <memory>
#include <vector>
#include <array>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Knight: public Piece
    {
        public:
            // Constructors
            Knight(Enums::Color color);
            Knight(Enums::Color color, bool has_moved, bool has_promoted);
            ~Knight() override = default;

            // Make a copy of this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get knight moves from a square
            // For each jump target: if on board and not friendly piece, include.
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;

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
#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Knight: public Piece
    {
        public:
            // Construct a Knight object with color
            Knight(Enums::Color color);
            ~Knight() override = default;

            // Make a clone of this Knight object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get all positions this Knight piece can move to from its current position
            std::vector<Position> GetPositionsFromJumpDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;

            // Get Knight moves from a position
            // For each jump target: if on board and not friendly piece, include.
            // !!! Does not check king safety
            std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const override;

            // Knight jump directions (8 L-shapes)
            static inline const std::vector<Direction> JumpDirs =
            {
                // North side jump
                Direction(-2, -1),
                Direction(-2,  1),

                // South side jump
                Direction( 2, -1),
                Direction( 2,  1),

                // West side jump
                Direction(-1, -2),
                Direction( 1, -2),

                // East side jump
                Direction(-1,  2),
                Direction( 1,  2)
            };
    };
} // namespace GameLogic

#endif
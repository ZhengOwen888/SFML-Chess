#ifndef GAMELOGIC_ROOK_HPP
#define GAMELOGIC_ROOK_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Rook: public Piece
    {
        public:
            // Construct a Rook object with color
            Rook(Enums::Color color);
            ~Rook() override;

            // Make a clone of this Rook object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get rook moves from a position
            // Steps:
            // - For each orthogonal dir, go step by step until off the board.
            // - Stop at the first piece. If enemy, include that position; if friendly, do not include it.
            std::vector<Move> GetPotentialMoves(const Position& from_position, const Board &board) const override;

            // Orthogonal directions: N, S, E, W
            static inline const std::vector<Direction> OrthogonalDirs =
            {
                Direction::North,
                Direction::South,
                Direction::East,
                Direction::West
            };
    };
} // namespace GameLogic

#endif
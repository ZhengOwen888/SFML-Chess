#ifndef GAMELOGIC_QUEEN_HPP
#define GAMELOGIC_QUEEN_HPP

#include "direction.hpp"
#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Queen: public Piece
    {
        public:
            // Construct a Queen object with color
            Queen(Enums::Color color);
            ~Queen() override;

            // Make a clone of this Queen object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get queen moves from a position
            // Combine rook + bishop logic (8 directions).
            // Walk each direction until off board or blocked; include first enemy then stop.
            // - Do not check king safety here.
            std::vector<Move> GetPotentialMoves(const Position& from_position, const Board &board) const override;

            // All 8 directions (orthogonal + diagonal)
            static inline const std::vector<Direction> AllDirs =
            {
                Direction::North,
                Direction::South,
                Direction::East,
                Direction::West,
                Direction::NorthEast,
                Direction::NorthWest,
                Direction::SouthEast,
                Direction::SouthWest
            };

    };
} // namespace GameLogic

#endif
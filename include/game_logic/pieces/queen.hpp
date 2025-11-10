#ifndef GAMELOGIC_QUEEN_HPP
#define GAMELOGIC_QUEEN_HPP

#include <memory>
#include <vector>
#include <array>

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

            // Make a clone of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get queen moves from a square
            // Combine rook + bishop logic (8 directions).
            // Walk each direction until off board or blocked; include first enemy then stop.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

            // All 8 directions (orthogonal + diagonal)
            static inline const std::array<Direction, 8>& AllSlideDirs()
            {
                static const std::array<Direction, 8> dirs = {
                    Direction::North, Direction::South, Direction::East, Direction::West,
                    Direction::NorthEast, Direction::NorthWest, Direction::SouthEast, Direction::SouthWest
                };
                return dirs;
            }
    };
} // namespace GameLogic

#endif
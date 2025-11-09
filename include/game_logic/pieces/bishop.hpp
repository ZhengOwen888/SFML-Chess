#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include <memory>
#include <vector>
#include <array>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // Constructors
            Bishop(Enums::Color color);
            Bishop(Enums::Color color, bool has_moved, bool has_promoted);
            ~Bishop() override = default;

            // Make a copy of this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get bishop moves from a square
            // Steps similar to rook but only diagonal directions.
            // Walk each diagonal until off board or blocked.
            // Include first enemy then stop; stop on friendly.
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;

            // Diagonal directions: NE, NW, SE, SW
            static inline const std::array<Direction, 4>& DiagonalDirs()
            {
                static const std::array<Direction, 4> dirs = {
                    Direction::NorthEast, Direction::NorthWest,
                    Direction::SouthEast, Direction::SouthWest
                };
                return dirs;
            }
    };
} // namespace GameLogic

#endif
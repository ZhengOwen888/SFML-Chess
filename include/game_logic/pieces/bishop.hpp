#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include <memory>
#include <vector>
#include <array>

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // construct Bishop object with color
            Bishop(Enums::Color color);
            ~Bishop() override;

            // Make a clone of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get bishop moves from a square
            // Steps similar to rook but only diagonal directions.
            // Walk each diagonal until off board or blocked.
            // Include first enemy then stop; stop on friendly.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

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
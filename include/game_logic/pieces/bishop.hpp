#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include "direction.hpp"
#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // Construct Bishop object with color
            Bishop(Enums::Color color);
            ~Bishop() override;

            // Make a clone of this Bishop object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get bishop moves from a position
            // Steps similar to Rook but only diagonal directions.
            // Walk each diagonal until off board or blocked.
            // Include first enemy then stop; stop on friendly.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

            // Diagonal directions: NE, NW, SE, SW
            static inline const std::vector<Direction> DiagonalDirs =
                {
                    Direction::NorthEast,
                    Direction::NorthWest,
                    Direction::SouthEast,
                    Direction::SouthWest
                };
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include "direction.hpp"
#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>
#include <array>

namespace GameLogic
{
    class King: public Piece
    {
        public:
            // Construct a King object with color
            King(Enums::Color color);
            ~King() override;

            // Make a clone of King object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get King moves from a position
            // For each adjacent position: if on board and (empty or enemy) include.
            // Castling is handled elsewhere.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

            // 8 adjacent directions
            static inline const std::array<Direction, 8>& AdjacentDirs()
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
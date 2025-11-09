#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include <memory>
#include <vector>
#include <array>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class King: public Piece
    {
        public:
            // Constructors
            King(Enums::Color color);
            King(Enums::Color color, bool has_moved, bool has_promoted);
            ~King() override = default;

            // Make a copy of this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get king moves from a square
            // For each adjacent square: if on board and (empty or enemy) include.
            // Castling is handled elsewhere.
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;

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
#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include <memory>
#include <vector>
#include <array>

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class King: public Piece
    {
        public:
            // construct a King object with color
            King(Enums::Color color);
            ~King() override;

            // make a clone of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get king moves from a square
            // For each adjacent square: if on board and (empty or enemy) include.
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
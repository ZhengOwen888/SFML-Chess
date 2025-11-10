#ifndef GAMELOGIC_ROOK_HPP
#define GAMELOGIC_ROOK_HPP

#include <memory>
#include <vector>
#include <array>

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Rook: public Piece
    {
        public:
            // construct a Rook object with color
            Rook(Enums::Color color);
            ~Rook() override;

            // Make a clone of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get rook moves from a square
            // Steps:
            // - For each orthogonal dir, go step by step until off the board.
            // - Stop at the first piece. If enemy, include that square; if friendly, do not include it.
            // - Do not check king safety here.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

            // Orthogonal directions: N, S, E, W
            static inline const std::array<Direction, 4>& OrthogonalDirs()
            {
                static const std::array<Direction, 4> dirs = {
                    Direction::North, Direction::South, Direction::East, Direction::West
                };
                return dirs;
            }
    };
} // namespace GameLogic

#endif
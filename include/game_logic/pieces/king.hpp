#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

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

            // Get potential positions that are 1 step away from the king in the 8 cardinal directions
            std::vector<Position> GetPositionsFromAdjacentDirs(
                const Position &from_position, const Board &board, const std::vector<Direction> &directions) const;

            // Get potential positions for king side and queen side castling
            std::vector<Position> GetPositionsFromCastling(
                const Position &from_position, const Board &board) const;

            // Returns true if the king can castle !!! Does not check for king safety
            bool CanCastle(
                const Position &king_position, const Position &rook_position,
                const std::vector<Position> &positions_in_between, const Board &board) const;

            // Get King moves from a position
            // For each adjacent position: if on board and (empty or enemy) include.
            // Castling is handled elsewhere.
            // !!! Does not check king safety
            std::vector<Move> GetPotentialMoves(const Position &from_position, const Board &board) const override;

            // 8 adjacent directions
            static inline const std::vector<Direction> AdjacentDirs =
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
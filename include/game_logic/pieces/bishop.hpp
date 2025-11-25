#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>
#include <optional>

namespace GameLogic
{
    class Bishop: public Piece
    {
        public:
            // Construct Bishop object with color
            Bishop(Enums::Color color);
            ~Bishop() override = default;

            // Make a clone of this Bishop object
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get bishop moves from a position
            // Steps similar to Rook but only diagonal directions.
            // Walk each diagonal until off board or blocked.
            // Include first enemy then stop; stop on friendly.
            // !!! Does not check king safety
            std::vector<Move> GetPotentialMoves(
                const Position &from_position, const Board &board, const Move* last_move = nullptr) const override;

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
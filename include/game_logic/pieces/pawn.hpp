#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include <memory>
#include <vector>
#include <array>
#include "piece.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Pawn: public Piece
    {
        public:
            // Constructors
            Pawn(Enums::Color color);
            Pawn(Enums::Color color, bool has_moved, bool has_promoted);
            ~Pawn() override = default;

            // Make a copy of this piece
            std::unique_ptr<Piece> clonePiece() const override;

            // Get pawn moves from a square (basic):
            // 1) One step forward: if empty include.
            // 2) Two steps: only if first move and both squares empty.
            // 3) Captures: check two diagonal targets; include if enemy there.
            // 4) Promotion / en passant handled later.
            std::vector<Move> getLegalMoves(const Position& from_position, Board &board) const override;

            // Forward direction by color (Light = North, Dark = South)
            static inline Direction Forward(Enums::Color color)
            {
                return (color == Enums::Color::Light) ? Direction::North : Direction::South;
            }

            static inline std::array<Direction,2> CaptureDirs(Enums::Color color)
            {
                if (color == Enums::Color::Light)
                {
                    return {Direction::NorthEast, Direction::NorthWest};
                }
                return {Direction::SouthEast, Direction::SouthWest};
            }
    };
} // namespace GameLogic

#endif
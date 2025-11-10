#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include <memory>
#include <vector>
#include <array>

#include "piece.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Pawn: public Piece
    {
        public:
            // construct a Pawn object with color
            Pawn(Enums::Color color);
            ~Pawn() override;

            // Make a copy of this piece
            std::unique_ptr<Piece> ClonePiece() const override;

            // Get pawn moves from a square (basic):
            // 1) One step forward: if empty include.
            // 2) Two steps: only if first move and both squares empty.
            // 3) Captures: check two diagonal targets; include if enemy there.
            // 4) Promotion / en passant handled later.
            std::vector<Move> GetLegalMoves(const Position& from_position, const Board &board) const override;

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
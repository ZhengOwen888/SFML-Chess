#ifndef GAMELOGIC_PAWN_HPP
#define GAMELOGIC_PAWN_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Pawn: public Piece
    {
        public:
            // Construct a Pawn object with color
            Pawn(Enums::Color color);
            ~Pawn() override;

            // Make a clone of this Pawn object
            std::unique_ptr<Piece> ClonePiece() const override;

            // checks if pawn can be promoted returns true if possible and false otherwise
            bool CanPromotePawn(const Position &forward_to_position, const Board &board) const;
            // Get pawn moves from a position (basic):
            // 1) One step forward: if empty include.
            // 2) Two steps: only if first move and both positions are empty.
            // 3) Captures: check two diagonal targets; include if enemy there.
            // 4) Promotion / en passant handled later.
            // !!! Does not check king safety
            std::vector<Move> GetPotentialMoves(const Position& from_position, const Board &board, const Move &last_move) const override;

            std::vector<Position> GetForwardPositions(const Position &from_position, const Board &board) const;
            std::vector<Position> GetCapturePositions(const Position &from_position, const Board &board, const Move &last_move) const;

            bool CanEnPassant(const Position &from_position, const Position &to_position, const Board& board, const Move &last_move) const;

            // Forward direction by color (Light = North, Dark = South)
            static inline Direction Forward(Enums::Color color)
            {
                return (color == Enums::Color::Light) ? Direction::North : Direction::South;
            }

            static inline std::vector<Direction> CaptureDirs(Enums::Color color)
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
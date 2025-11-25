#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    // Forward direction to avoid circular imports
    class Board;

    class Piece
    {
        public:
            // Construct a Piece object with piece type and color
            Piece(Enums::PieceType piece_type, Enums::Color color);
            virtual ~Piece() = default;

            // Clone a new Piece object with the same properties
            virtual std::unique_ptr<Piece> ClonePiece() const = 0;

            // Get all potential moves
            virtual std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const = 0;

            // Get all positions a piece can move to from its current position (in EXACTLY ONE Direction)
            std::vector<Position> GetPositionsInDir(
                const Position& from_position, const Board &board, const Direction& direction) const;

            // Get all positions a piece can move to from its current position (in a SET of MANY Directions)
            std::vector<Position> GetPositionsInDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;

            // Setters
            void SetHasMoved(bool has_moved);
            void SetHasPromoted(bool has_promoted);

            // Getters
            Enums::PieceType GetPieceType() const;
            Enums::Color GetColor() const;
            bool HasMoved() const;
            bool HasPromoted() const;

        protected:
            Enums::PieceType piece_type_;
            Enums::Color color_;
            bool has_moved_;    // false initially
            bool has_promoted_; // false initially
    };
} // namespace GameLogic

#endif
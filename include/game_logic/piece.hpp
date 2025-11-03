#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    // forward direction to avoid circular imports
    class Board;

    class Piece
    {
        public:
            // construct a Piece object with piece type and color
            Piece(Enums::PieceType piece_type, Enums::Color color);
            virtual ~Piece();

            // clone a new Piece object with the same properties
            virtual std::unique_ptr<Piece> ClonePiece() const = 0;

            // get all legal moves
            virtual std::vector<Move> GetLegalMoves(
                const Position& from_position, const Board &board) const = 0;

            // get all positions a piece can move to from its current position (in EXACTLY ONE Direction)
            std::vector<Position> GetPositionsInDir(
                const Position& from_position, const Board &board, const Direction& direction) const;

            // get all positions a piece can move to from its current position (in a SET of MANY Directions)
            std::vector<Position> GetPositionsInDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;

            // setters
            void SetHasMoved();
            void SetHasPromoted();

            // getters
            Enums::PieceType GetPieceType() const;
            Enums::Color GetColor() const;
            bool HasMoved() const;
            bool HasPromoted() const;

        private:
            Enums::PieceType piece_type_;
            Enums::Color color_;
            bool has_moved_;    // false initially
            bool has_promoted_; // false initially
    };
} // namespace GameLogic

#endif
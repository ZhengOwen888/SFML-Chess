#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include <memory>
#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"

namespace GameLogic
{
    class Board; // forward direction to avoid circular imports

    class Piece
    {
        public:
            // Construct a piece with their color and or has_moved, has_promoted
            Piece(Enums::PieceType piece_type, Enums::Color color);
            Piece(Enums::PieceType piece_type, Enums::Color color, bool has_moved, bool has_promoted);
            virtual ~Piece() = default;

            // Clone creates a new piece object with the same property and values
            virtual std::unique_ptr<Piece> clonePiece() const = 0;

            // get all legal moves
            virtual std::vector<Move> getLegalMoves(
                const Position& from_position, Board &board) const = 0;

            // helper for getPositionsInDirs: it gets all the positions in one certain directioin if it is legal
            std::vector<Position> getPositionsInDir(
                const Position& from_position, Board &board, const Direction& direction);

            // helper for getLegalMoves: it gets all the positions in many directions if it is legal
            std::vector<Position> getPositionsInDirs(
                const Position& from_position, Board &board, const std::vector<Direction>& directions);

            // Setters
            void setHasMoved();
            void setHasPromoted();

            // Getters
            Enums::PieceType getPieceType() const;
            Enums::Color getColor() const;
            bool hasMoved() const;
            bool hasPromoted() const;

        private:
            Enums::PieceType piece_type_;
            Enums::Color color_;
            bool has_moved;    // false initially
            bool has_promoted; // false initially
    };
} // namespace GameLogic

#endif
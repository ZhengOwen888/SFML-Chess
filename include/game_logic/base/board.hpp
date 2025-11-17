#ifndef GAMELOGIC_BOARD_HPP
#define GAMELOGIC_BOARD_HPP

#include "game_logic/base/piece.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{
    class Board
    {
        public:
            // Construct a Board object
            Board();
            ~Board();

            // Helpers used to execute moves
            // Make a Normal move for a Piece object from one position to another on the board
            bool MovePiece(const Position &from_position, const Position &to_position, bool simulate = false);

            // Remove a Piece object at a position on the board
            void RemovePieceAt(const Position &position);

            // Place a Piece object at a position on the board
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position);

            // Take a pointer to a Piece object at a position
            std::unique_ptr<Piece> TakePieceAt(const Position &position);

            // Returns an immutable piece at a given position otherwise nullptr (for read purpose only)
            const Piece* GetPieceAt(const Position &position) const;

            // Returns a mutable piece at a given position otherwise nullptr
            Piece* GetMutablePieceAt(const Position &position);

            // Returns true if position is inside board and false otherwise
            bool IsPositionOnBoard(const Position &position) const;

            // Returns true of positions has no piece on it and false otherwise
            bool IsPositionEmpty(const Position &position) const;

            // Returns true if a list of specified positions are empty
            bool ArePositionsEmpty(const std::vector<Position> &positions) const;

        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            // Castling rights tracking (initialized as true, set to false when king/rook moves)
            bool can_castle_light_king_side_;
            bool can_castle_light_queen_side_;
            bool can_castle_dark_king_side_;
            bool can_castle_dark_queen_side_;

            // Set up all pieces in starting positions
            void InitializeBoard();
    };
}

#endif
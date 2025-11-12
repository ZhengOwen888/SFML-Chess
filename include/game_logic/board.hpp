#ifndef GAMELOGIC_BOARD_HPP
#define GAMELOGIC_BOARD_HPP

#include "piece.hpp"
#include "move.hpp"
#include "position.hpp"

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

            // Execute a move
            bool ExecuteMove(const Move& move);

            // Get all legal moves for a piece at a given position
            std::vector<Move> GetLegalMovesAtPosition(const Position& position);

            // Returns an immutable piece at a given position otherwise nullptr (for read purpose only)
            const Piece* GetPieceAt(const Position &position) const;

            // Returns a mutable piece at a given position otherwise nullptr
            Piece* GetMutablePieceAt(const Position &position);

            // Returns true if position is inside board and false otherwise
            bool IsPositionOnBoard(const Position &position) const;

            // Returns true of positions has no piece on it and false otherwise
            bool IsPositionEmpty(const Position &position) const;

        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            // Set up all pieces in starting positions
            void InitializeBoard();

            // Helpers used to execute moves
            // Make a Normal move for a Piece object from one position to another on the board
            bool MovePiece(const Position &from_position, const Position &to_position);

            // Remove a Piece object at a position on the board
            void RemovePieceAt(const Position &position);

            // Place a Piece object at a position on the board
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position);

            // Take a pointer to a Piece object at a position
            std::unique_ptr<Piece> TakePieceAt(const Position &position);

            // Helpers used for finding legal moves
            // Returns true if any one of the piece can capture the opponent's players king
            bool CanCaptureKing(Enums::Color player_color) const;

            // Returns true if the player's king is in check
            bool IsKingInCheck(Enums::Color player_color) const;

            // Returns true if a normal move would result in the player's king to be in check
            bool NormalMoveLeaveKingInCheck(const Move &move, Enums::Color player_color);

            // Returns true if the move is legal
            bool IsLegalMove(const Move &move, Enums::Color player_color);
    };
}

#endif
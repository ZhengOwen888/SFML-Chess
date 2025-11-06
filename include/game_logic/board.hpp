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
            // construct a Board object
            Board();
            ~Board();

            // execute a move
            bool ExecuteMove(const Move& move);

            // returns an immutable piece at a given position otherwise nullptr (for read purpose only)
            const Piece* GetPieceAt(const Position &position) const;

            // returns a mutable piece at a given position otherwise nullptr
            Piece* GetMutablePieceAt(const Position &position);

            // returns true if position is inside board and false otherwise
            bool IsPositionOnBoard(const Position &position) const;

            // returns true of positions has no piece on it and false otherwise
            bool IsPositionEmpty(const Position &position) const;

        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            // set up all pieces in starting positions
            void InitializeBoard();

            // helpers used to execute moves
            // move a Piece object from one position to another on the board
            void MovePiece(const Position& from_position, const Position& to_position);

            // remove a Piece object at a position on the board
            void RemovePieceAt(const Position& position);

            // place a Piece object at a position on the board
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position& position);

            // take a pointer to a Piece object at a position
            std::unique_ptr<Piece> TakePieceAt(const Position &position);
    };
}

#endif
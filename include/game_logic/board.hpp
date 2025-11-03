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

            // set up all pieces in starting positions
            void InitializeBoard();

            // execute a move
            void ExecuteMove(const Move& move);

            // returns an immutable piece at a given position otherwise nullptr (for read purpose only)
            const Piece* GetPieceAt(int row, int col) const;
            const Piece* GetPieceAt(const Position &position) const;

            // returns a mutable piece at a given position otherwise nullptr
            Piece* GetMutablePieceAt(int row, int col) const;
            Piece* GetMutablePieceAt(const Position &position) const;

            // returns true if position is inside board and false otherwise
            bool IsPositionOnBoard(int row, int col) const;
            bool IsPositionOnBoard(const Position &position) const;

            // returns true of positions has no piece on it and false otherwise
            bool IsPositionEmpty(int row, int col) const;
            bool IsPositionEmpty(const Position &position) const;

        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            // helpers used to execute moves
            void MovePiece(const Position& from_position, const Position& to_position);
            void RemovePieceAt(const Position& position);
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position& position);
    };
}

#endif
#ifndef GAMELOGIC_BOARD_HPP
#define GAMELOGIC_BOARD_HPP

#include "piece.hpp"
#include <vector>

namespace GameLogic
{
    class Board
    {
        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<Piece>> pieces;

            // modifies the 2d vector to make put all pieces in their starting positions
            void SetStartingPositions();

        public:
            // returns a piece if it is on square and null otherwise
            Piece GetSquare(int row, int col);

            // sets a square on the board to a piece or null
            // returns void and piece is passed by reference
            void SetSquare(int row, int col, Piece &piece);

            // set up all pieces in starting positions and returns board object
            Board Initialize();

            // returns true if position is inside board and false otherwise
            bool IsInside(int row, int col);

            // returns true of positions has no piece on it and false otherwise
            bool IsEmpty(int row, int col);

    };
}


#endif

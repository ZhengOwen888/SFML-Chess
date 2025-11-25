#ifndef GAMELOGIC_POSITION_HPP
#define GAMELOGIC_POSITION_HPP

#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    /*************************************************************************
     * @class Position
     * @brief Represents a specific coordinate (square) on an 8x8 chess board.
     *
     * Positions use 0 based indexing (0-7) for both row and column.
     ************************************************************************/
    class Position
    {
        public:
            /** @brief Default Constructor, initialize Position to (0, 0). */
            Position() = default;

            /*************************************************************
             * @brief Contruct a Position with a row and column.
             * @param row the row position on the chess board.
             * @param col the col position on the chess board.
             *
             * The position is 0 based.
             * Example:
             *  a8:(rank(row): 8, file(col): a) = Position(row: 0, col: 0)
             *  h1:(rank(row): 1, file(col): h) = Position(row: 7, col: 7)
             ************************************************************/
            Position(int row, int col);

            /** Default Destructor */
            ~Position() = default;

            /*******************************************************************************
             * @brief Equality operator overload to compare two position objects.
             * @param other_position The other position to compare against.
             * @return true if the row and col of both positions are equal, false otherwise.
             ******************************************************************************/
            bool operator==(const Position& other_position) const;

            /***************************************************************************************************************
             * @brief Less than operator overload, useful for storing Positions in std::map or std::set.
             * @param other_position The other position to compare against.
             * @return true if this position is less than the other position by lexicographical comparison, false otherwise.
             **************************************************************************************************************/
            bool operator<(const Position& other_position) const;

            /******************************************************************************
             * @brief Add direction to position to get new position.
             * @param other_direction Direction to move in (row and col deltas).
             * @return New direction after applying direction.
             *
             * Example: Position(3, 3) + Direction::North which is (-1, 0) = Position(2, 3)
             *****************************************************************************/
            Position operator+(const Direction &other_direction) const;

            /***********************************************************************
             * @brief Get the color of this square at this position.
             * @return Color::Light or Color::Dark based on this position.
             *
             * Chess board squares alternate colors. Formula: (row + col) % 2
             * If the result is even then the it Color::Light otherwise Color::Dark.
             * Example: Position(0, 0) = Color::Light, Position(2, 3) = Color::Dark
             **********************************************************************/
            Enums::Color GetSquareColor() const;

            /*************************************************
             * @brief Gets the row index of this position.
             * @return The 0 based row (0-7) of this position.
             ************************************************/
            int GetRow() const;

            /*************************************************
             * @brief Gets the col index of this position.
             * @return The 0 based col (0-7) of this position.
             ************************************************/
            int GetCol() const;

        private:
            /** @brief The 0 based row index (0-7). */
            int row_;

            /** @brief The 0 based col index (0-7). */
            int col_;
    };
} // namespace GameLogic

#endif
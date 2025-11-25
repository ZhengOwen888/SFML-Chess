#ifndef GAMELOGIC_POSITION_HPP
#define GAMELOGIC_POSITION_HPP

#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    class Position
    {
        public:
            Position() = default;
            /**
             * @brief Contruct a Position
             * @param row the row position on the chess board
             * @param col the col position on the chess board
             *
             * The position is 0 based
             * Example:
             *  (rank: 8, file: a) = Position(0, 0)
             *  (rank: 1, file: h) = Position(7, 7)
             */
            Position(int row, int col);
            ~Position() = default;

            /** @return true if the row and col of both positions are equal, false otherwise */
            bool operator==(const Position& other_position) const;

            /** @return true if this position is less than the other position by lexicographical comparison*/
            bool operator<(const Position& other_position) const;

            /**
             * @brief Add direction to position to get new position
             * @param other_direction Direction to move in (row and col deltas)
             * @return New direction after applying direction
             *
             * Example: Position(3, 3) + Direction::North which is (-1, 0) = Position(2, 3)
             */
            Position operator+(const Direction &other_direction) const;

            /**
             * @brief Get the color of this square at this position
             * @return Color::Light or Color::Dark based on this position
             *
             * Chess board squares alternate colors. Formula: (row + col) % 2
             * If the result is even then the it Color::Light otherwise Color::Dark
             * Example: Position(0, 0) = Color::Light, Position(2, 3) = Color::Dark
             */
            Enums::Color GetSquareColor() const;

            /** @return The row of this position */
            int GetRow() const;

            /** @return The col of this position */
            int GetCol() const;

        private:
            int row_;
            int col_;
    };
} // namespace GameLogic

#endif
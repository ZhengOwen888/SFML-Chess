#ifndef GAMELOGIC_POSITION_HPP
#define GAMELOGIC_POSITION_HPP

#include "enums.hpp"

#include "direction.hpp"

namespace GameLogic
{
    class Position
    {
        public:
            // Construct a position with row and col
            Position(int row, int col);
            ~Position();

            // Check if two position are equal
            bool operator==(const Position& other_position) const;

            // Adding directions and steps to position
            Position operator+(const Direction &other_direction) const;

            // Getters
            Enums::Color getColor() const; // calculate color of the square
            int getRow() const;
            int getCol() const;

        private:
            int row_;
            int col_;
    };
} // namespace GameLogic

#endif
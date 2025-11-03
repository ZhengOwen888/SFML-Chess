#ifndef GAMELOGIC_POSITION_HPP
#define GAMELOGIC_POSITION_HPP

#include "enums.hpp"
#include "direction.hpp"

namespace GameLogic
{
    class Position
    {
        public:
            // construct a Position object with row and column
            Position(int row, int col);
            ~Position();

            // returns true if this position and another position are eqaul in terms of row and column
            bool operator==(const Position& other_position) const;

            // returns a new Position object by adding change in row and change column to this position's row and column respectively
            Position operator+(const Direction &other_direction) const;

            // Getters
            Enums::Color GetSquareColor() const;
            int GetRow() const;
            int GetCol() const;

        private:
            int row_;
            int col_;
    };
} // namespace GameLogic

#endif

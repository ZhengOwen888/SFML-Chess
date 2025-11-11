#include "direction.hpp"

namespace GameLogic
{
    // Construct a Direction object with change in rows and change in columns
    Direction::Direction(int row_delta, int col_delta)
        : row_delta_(row_delta), col_delta_(col_delta) {};

    // Default destructor
    Direction::~Direction() {};


    // Return a new Direction object with the sum of this direction and another direction
    Direction Direction::operator+(const Direction& other_direction) const
    {
        return Direction(
            this->row_delta_ + other_direction.row_delta_,
            this->col_delta_ + other_direction.col_delta_
        );
    }

    // Return a new Direction with the scalar of this direction
    Direction Direction::operator*(int scalar) const
    {
        return Direction(
            this->row_delta_ * scalar,
            this->col_delta_ * scalar
        );
    }


    // Return the change in row of this direction
    int Direction::GetRowDelta() const
    {
        return this->row_delta_;
    }

    // Return the change in column of this direction
    int Direction::GetColDelta() const
    {
        return this->col_delta_;
    }


    // 8 cardinal directions
    const Direction Direction::North(-1, 0);
    const Direction Direction::South(1, 0);
    const Direction Direction::East(0, 1);
    const Direction Direction::West(0, -1);
    const Direction Direction::NorthEast = North + East; // (-1,  1)
    const Direction Direction::NorthWest = North + West; // (-1, -1)
    const Direction Direction::SouthEast = South + East; // ( 1,  1)
    const Direction Direction::SouthWest = South + West; // ( 1, -1)

} // namespace GameLogic
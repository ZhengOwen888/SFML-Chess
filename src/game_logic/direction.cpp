#include "direction.hpp"

namespace GameLogic
{
    // construct a Direction object with change in rows and change in columns
    Direction::Direction(int row_delta, int col_delta)
        : row_delta_(row_delta), col_delta_(col_delta) {};

    // default destructor
    Direction::~Direction() {};


    // return a new Direction object with the sum of this direction and another direction
    Direction Direction::operator+(const Direction& other_direction) const
    {
        return Direction(
            row_delta_ + other_direction.row_delta_,
            col_delta_ + other_direction.col_delta_
        );
    }

    // return a new Direction with the scalar of this direction
    Direction Direction::operator*(int scalar) const
    {
        return Direction(
            row_delta_ * scalar,
            col_delta_ * scalar
        );
    }


    // return the change in row of this direction
    int Direction::GetRowDelta() const
    {
        return row_delta_;
    }

    // return the change in column of this direction
    int Direction::GetColDelta() const
    {
        return col_delta_;
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
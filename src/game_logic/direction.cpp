#include "direction.hpp"

namespace GameLogic
{
    Direction::Direction(int row_delta, int col_delta)
        : row_delta_(row_delta), col_delta_(col_delta) {};

    Direction::~Direction() {};

    Direction Direction::operator+(const Direction& other_direction) const
    {
        return Direction(
            row_delta_ + other_direction.row_delta_,
            col_delta_ + other_direction.col_delta_
        );
    }

    Direction Direction::operator*(int scalar) const
    {
        return Direction(
            row_delta_ * scalar,
            col_delta_ * scalar
        );
    }

    int Direction::getRowDelta() const
    {
        return row_delta_;
    }

    int Direction::getColDelta() const
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
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"

namespace GameLogic
{
    Position::Position(int row, int col)
        : row_(row), col_(col) {};

    Position::~Position() {};

    bool Position::operator==(const Position& other_position) const
    {
        return (row_ == other_position.row_) && (col_ == other_position.col_);
    }

    Position Position::operator+(const Direction &other_direction) const
    {
        return Position(
            row_ + other_direction.getRowDelta(),
            col_ + other_direction.getColDelta()
        );
    }

    Enums::Color Position::getSquareColor() const
    {
        if (row_ % 2 == col_ % 2)
        {
            return Enums::Color::Light;
        }

        return Enums::Color::Dark;
    }

    int Position::getRow() const
    {
        return row_;
    }

    int Position::getCol() const
    {
        return col_;
    }
} // namespace GameLogic
#include "game_logic/base/position.hpp"
#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    // Construct a Position object with row and column
    Position::Position(int row, int col)
        : row_(row), col_(col) {};

    // Default destructor
    Position::~Position() {};

    // Returns true if this position and another position are eqaul in terms of row and column
    bool Position::operator==(const Position& other_position) const
    {
        return this->row_ == other_position.row_
            && this->col_ == other_position.col_;
    }

    // Returns a new Position object by adding change in row and change column to this position's row and column respectively
    Position Position::operator+(const Direction &other_direction) const
    {
        return Position(
            this->row_ + other_direction.GetRowDelta(),
            this->col_ + other_direction.GetColDelta()
        );
    }

    // Return the color of the square on the board at this position
    Enums::Color Position::GetSquareColor() const
    {
        if (this->row_ % 2 == this->col_ % 2)
        {
            return Enums::Color::Light;
        }

        return Enums::Color::Dark;
    }

    // Return the row of this position
    int Position::GetRow() const
    {
        return this->row_;
    }

    // Return the column of this position
    int Position::GetCol() const
    {
        return this->col_;
    }
} // namespace GameLogic
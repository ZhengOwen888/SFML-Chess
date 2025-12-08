#include "game_logic/base/position.hpp"
#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"

#include <string>

namespace GameLogic
{
    // Construct a Position object with row and column
    Position::Position(int row, int col)
        : row_(row), col_(col) {};

    // Returns true if this position and another position are eqaul in terms of row and column
    bool Position::operator==(const Position& other_position) const
    {
        return this->row_ == other_position.row_
            && this->col_ == other_position.col_;
    }

    // Returns true if this position is less than the other position by lexigraphical comparison
    bool Position::operator<(const Position& other_position) const
    {
        if (this->row_ != other_position.row_)
        {
            return this->row_ < other_position.row_;
        }

        return this->col_ < other_position.col_;
    }

    // Returns a new Position object by adding change in row and change column to this position's row and column respectively
    Position Position::operator+(const Direction &other_direction) const
    {
        return Position(
            this->row_ + other_direction.GetRowDelta(),
            this->col_ + other_direction.GetColDelta()
        );
    }

    std::string Position::PositionToAlgebraic() const
    {
        char file = 'a' + this->col_;
        char rank = '8' - this->row_;

        return std::string(1, file) + std::string(1, rank);
    }

    Position Position::AlgebraicToPosition(char file, char rank)
    {
        int col = file - 'a';
        int row = '8' - rank;

        return Position{row, col};
    }

    // Return the color of the square on the board at this position
    Enums::Color Position::GetSquareColor() const
    {
        if ((this->row_ + this->col_) % 2 == 0)
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
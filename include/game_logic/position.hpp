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



//     // default destructor
//     Position::~Position() {};

//     // returns true if this position and another position are eqaul in terms of row and column
//     bool Position::operator==(const Position& other_position) const
//     {
//         return (row_ == other_position.row_) && (col_ == other_position.col_);
//     }

//     // returns a new Position object by adding change in row and change column to this position's row and column respectively
//     Position Position::operator+(const Direction &other_direction) const
//     {
//         return Position(
//             row_ + other_direction.GetRowDelta(),
//             col_ + other_direction.GetColDelta()
//         );
//     }

//     // return the color of the square on the board at this position
//     Enums::Color Position::GetSquareColor() const
//     {
//         if (row_ % 2 == col_ % 2)
//         {
//             return Enums::Color::Light;
//         }

//         return Enums::Color::Dark;
//     }

//     // return the row of this position
//     int Position::GetRow() const
//     {
//         return row_;
//     }

//     // return the column of this position
//     int Position::GetCol() const
//     {
//         return col_;
//     }
// } // namespace GameLogic
#ifndef GAMELOGIC_DIRECTION_HPP
#define GAMELOGIC_DIRECTION_HPP

namespace GameLogic
{
    class Direction
    {
        public:
            // Construct a direction with row and col deltas
            Direction(int row_delta, int col_delta);
            ~Direction();

            // Vector addition, adding two directions
            Direction operator+(const Direction &other_direction) const;

            // Scalar multiplication, scale direction
            Direction operator*(int scalar) const;

            // Getters
            int getRowDelta() const;
            int getColDelta() const;

            // static chess directions
            static const Direction North;
            static const Direction South;
            static const Direction East;
            static const Direction West;
            static const Direction NorthEast;
            static const Direction NorthWest;
            static const Direction SouthEast;
            static const Direction SouthWest;

        private:
            int row_delta_; // change in row (-1 = up, 1 = down)
            int col_delta_; // change in col (-1 = left, 1 = right)
    };
}

#endif
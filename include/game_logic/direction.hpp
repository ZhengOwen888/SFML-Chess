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
            static const Direction North;     // (-1,  0)
            static const Direction South;     // ( 1,  0)
            static const Direction East;      // ( 0,  1)
            static const Direction West;      // ( 0, -1)
            static const Direction NorthEast; // (-1,  1) or North + East
            static const Direction NorthWest; // (-1, -1) or North + West
            static const Direction SouthEast; // ( 1,  1) or South + East
            static const Direction SouthWest; // ( 1, -1) or South + West

        private:
            int row_delta_; // change in row (-1 = up, 1 = down)
            int col_delta_; // change in col (-1 = left, 1 = right)
    };
} // namespace GameLogic

#endif
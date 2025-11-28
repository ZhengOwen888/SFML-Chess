#ifndef GAMELOGIC_DIRECTION_HPP
#define GAMELOGIC_DIRECTION_HPP

namespace GameLogic
{
    /**********************************************************************************************
     * @class Direction
     * @brief Represents a change in position on an 8x8 board, defined by row and column deltas.
     *
     * This class is useful for calculating movement vectors for chess pieces and validating moves.
     * It supports basic arithmetic operations (addition, scalar multiplication).
     *********************************************************************************************/
    class Direction
    {
        public:
            /** @brief default Constructor, initialize Direction(0, 0). */
            Direction() = default;

            /** **********************************************************************
             * @brief Constructs a Direction object with specific row and col changes.
             * @param row_delta the change in row index.
             * @param col_delta the change in col index.
             ************************************************************************/
            Direction(int row_delta, int col_delta);

            /** @brief default Destructor for the Direction class. */
            ~Direction() = default;

            /** ***************************************************************************
             * @brief Overload addition operator to add two Directions.
             * @param other_direction The other Direction to be added.
             * @return A new Direction object that represents the sum of the two Directions
             *****************************************************************************/
            Direction operator+(const Direction &other_direction) const;

            /** ************************************************************
             * @brief Overload multiplication operator to scale a Direction.
             * @param scalar How much the Direction will be scaled.
             * @return A new Direction object that is scaled
             **************************************************************/
            Direction operator*(int scalar) const;

            /****************************
             * @brief Gets the row delta.
             * @return The change in row.
             ***************************/
            int GetRowDelta() const;

            /****************************
             * @brief Gets the col delta.
             * @return The change in col.
             ***************************/
            int GetColDelta() const;

            // --- Static Cardinal Directions (From First Player's (Light) perspective) --- //

            /** @brief The Direction pointing up (-1,  0) */
            static const Direction North;

            /** @brief The Direction pointing down ( 1,  0) */
            static const Direction South;

            /** @brief The Direction pointing right ( 0,  1) */
            static const Direction East;

            /** @brief The Direction pointing left ( 0, -1) */
            static const Direction West;

            /** @brief The Direction pointing up-right (-1,  1) */
            static const Direction NorthEast;

            /** @brief The Direction pointing up-left (-1, -1) */
            static const Direction NorthWest;

            /** @brief The Direction pointing down-right ( 1,  1) */
            static const Direction SouthEast;

            /** @brief The Direction pointing down-left ( 1, -1) */
            static const Direction SouthWest;

        private:
            /** @brief Change in row index, row (-1 = up, 1 = down)*/
            int row_delta_;

            /** @brief Change in col index col (-1 = left, 1 = right)*/
            int col_delta_;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include "game_logic/base/position.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    /**************************************************************************************
     * @class Move
     * @brief Represents a single potential or executed move on a chess board.
     *
     * This class stores the start and end positions, as well as the specific type of move
     * (normal, castle, promotion, etc.) which is crucial for handling complex chess rules.
     *************************************************************************************/
    class Move
    {
        public:
            /** @brief Default Constructor. */
            Move() = default;

            /********************************************************************************************
             * @brief Construct a Move object with the move type, start position and destination position
             * @param move_type The type of Move that was made (Normal, DoublePawn, ...)
             * @param from_position The starting position of the piece that will be moved.
             * @param to_position The destination position of the piece after making the Move.
             ********************************************************************************************/
            Move(Enums::MoveType move_type, const Position&  from_position, const Position& to_position);

            /** @brief Default Destructor. */
            ~Move() = default;

            /************************************************************************************************
             * @brief Check the equality of two Move objects
             * @param other_move The other move to be compared
             * @return true if both Moves have the same move type, starting position and destination position
             ***********************************************************************************************/
            bool operator==(const Move &other_move) const;


            /********************************************************
             * @brief Get the type of the Move
             * @return The type of the Move (Normal, DoublePawn, ...)
             *******************************************************/
            Enums::MoveType GetMoveType() const;

            /***************************************************************
             * @brief Get the starting Position
             * @return The Position from which the Piece will be moved from.
             **************************************************************/
            const Position& GetFromPosition() const;

            /**********************************************************************
             * @brief Get the destination Position
             * @return The Position where the Piece will be after the Move is made.
             *********************************************************************/
            const Position& GetToPosition() const;

        private:
            /** @brief The type of the Move (Normal, DoublePawn, Enpassant, ...) */
            Enums::MoveType move_type_;

            /** @brief The tarting Position. */
            Position from_position_;

            /** @brief The destination Position. */
            Position to_position_;
    };
} // namespace GameLogic

#endif
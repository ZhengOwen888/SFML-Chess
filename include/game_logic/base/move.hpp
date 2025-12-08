#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include "game_logic/base/position.hpp"

#include "game_logic/enums.hpp"

#include <tuple>


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

            /*******************************************************************************************
             * @brief Set the type of piece the pawn will be promoted to when it gets to the final rank.
             * @param promotion_piece_type The piece the pawn will be promoted to.
             ******************************************************************************************/
            void SetPromotionPieceType(Enums::PieceType promotion_piece_type);

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

            /**************************************************
             * @brief Get the promotion piece type for pawns.
             * @return The piece that the pawn will promote to.
             *************************************************/
            Enums::PieceType GetPromotionPieceType() const;

            /***************************************************************************************
             * @brief Creates a Move object from a standard UCI move string (e.g., "e2e4", "a7a8q").
             * @param uci_string The move in UCI format.
             * @return A tuple of start position, destination and the promotion type.
             **************************************************************************************/
            static std::tuple<Position, Position, Enums::PieceType> FromUCI(const std::string &uci_string);

        private:
            /** @brief The type of the Move (Normal, DoublePawn, Enpassant, ...) */
            Enums::MoveType move_type_;

            /** @brief The tarting Position. */
            Position from_position_;

            /** @brief The destination Position. */
            Position to_position_;

            /** @brief The piece that the pawn will be promoted to. */
            Enums::PieceType promotion_piece_type_;
    };
} // namespace GameLogic

#endif
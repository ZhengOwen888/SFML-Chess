#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/direction.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    // Forward declaration to avoid circular imports.
    // The Piece class only interact with the board via references and pointers.
    class Board;

    /**********************************************************************************
     * @class Piece
     * @brief An abstract base class representing a generic chess piece.
     *
     * This class defines the interface and shared state (color, type, movement status)
     * for all specific chess piece types (Pawn, King, Queen, ...).
     *********************************************************************************/
    class Piece
    {
        public:
            /***************************************************************************
             * @brief Construct a Piece object with the type of the piece and its color.
             * @param piece_type The type of the Piece (Pawn, King, Queen, ...)
             * @param color The color of the Piece (Dark, Light)
             **************************************************************************/
            Piece(Enums::PieceType piece_type, Enums::Color color);

            /** @brief A virtual Default Destructor to ensure that the derived piece classes are cleaned up correctly*/
            virtual ~Piece() = default;

            /******************************************************************************
             * @brief Creates a deep copy (clone) of the current Piece object.
             * This is a pure virtual function that must be implemented by derived classes.
             * @return A unique_ptr to the newly created clone.
             ******************************************************************************/
            virtual std::unique_ptr<Piece> ClonePiece() const = 0;

            /**************************************************************************************************************************
             * @brief Calculates all potential moves the Piece can make according to its movement rules.
             *
             * This is a pure virtual function must be implemented by derived classes.
             * !!! IMPORTANT: This method calculates *potential* moves based on piece mechanics only.
             * !!! IMPORTANT: This method does not check for King safety
             *
             * @param from_position The current position of the Piece on the board.
             * @param board The current state of the Board that is used for validation.
             * @param last_move Optional pointer to the last move made in the game (Needed for En Passant logic).
             * @return A vector of potential Move objects.
             **************************************************************************************************************************/
            virtual std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const = 0;

            /**************************************************************************************************
             * @brief Helper function to calculate the position a Piece can move to in EXACTLY ONE Drirection.
             *
             * This funciton also ignored king safety.
             *
             * @param from_position The current position of the Piece on the board.
             * @param board The current state of the Board that is used for validation (Boundary and Occupancy).
             * @param direction The Continuous Direction the Piece will travel in.
             * @return A vector of valid Positions along the Direction.
             **************************************************************************************************/
            std::vector<Position> GetPositionsInDir(
                const Position& from_position, const Board &board, const Direction& direction) const;

            /******************************************************************************************************
             * @brief Helper function to calculate the position a Piece can move to from a LIST of MANY Directions.
             *
             * This funciton also ignored king safety.
             *
             * @param from_position The current position of the Piece on the board.
             * @param board The current state of the Board that is used for validation (Boundary and Occupancy).
             * @param directions A vector of Directions the piece will travel in.
             * @return A vector of valid Positions along all the Directions provided.
             ****************************************************************************************************/
            std::vector<Position> GetPositionsInDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;


            // -- Setters -- //

            /******************************************************************
             * @brief Sets whether the piece has moved from its initial square.
             * @param has_moved The new state (true if moved, false otherwise).
             ******************************************************************/
            void SetHasMoved(bool has_moved);

            /*************************************************************************************
             * @brief Sets whether the pawn has promoted.
             * @param has_promoted The piece that was promoted (true if promoted, false otherwise)
             ************************************************************************************/
            void SetHasPromoted(bool has_promoted);


            // -- Getters -- //

            /********************************************
             * @brief Gets the type of the Piece.
             * @return The Enums::PieceType of the Piece.
             *******************************************/
            Enums::PieceType GetPieceType() const;

            /****************************************
             * @brief Gets the Color of the Piece.
             * @return The Enums::Color of the Piece.
             ***************************************/
            Enums::Color GetColor() const;

            /****************************************************************************************************
             * @brief Checks if the Piece has previously moved in the game (Used for castling, double pawn push).
             * @return true if the Piece has moved, false otherwise.
             ***************************************************************************************************/
            bool HasMoved() const;

            /***********************************************************
             * @brief Checks if the Piece is a result of pawn promotion.
             * @return true if Piece was promoted, false otherwise.
             **********************************************************/
            bool HasPromoted() const;

        protected:
            /** @brief The identifier for the type of the Piece. */
            Enums::PieceType piece_type_;

            /** @brief The identifier for the color of the Piece. */
            Enums::Color color_;

            /** @brief Flag indicating if the piece has ever moved from its starting square. (False initially) */
            bool has_moved_;

            /** @brief Flag indicating if the pawn has ever promoted. (False initially) */
            bool has_promoted_;
    };
} // namespace GameLogic

#endif
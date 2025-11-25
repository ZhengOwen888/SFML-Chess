#ifndef GAMELOGIC_KING_HPP
#define GAMELOGIC_KING_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    /*******************************************************************************
     * @class King
     * @brief Represents the King chess piece.
     *
     * Inherits from the abstract base class `Piece` and implements the specific
     * movement logic for a King, including standard single step moves and castling.
     ******************************************************************************/
    class King: public Piece
    {
        public:
            /**********************************************************
             * @brief Constructs a King Object with a specific color.
             * @param color The color (Light or Dark) of the King.
             *********************************************************/
            King(Enums::Color color);

            /** @brief  Virtual Default Destructor*/
            ~King() override = default;

            /*********************************************************
             * @brief Creates a deep copy (clone) of this King object.
             * @return A unique_ptr to the newly created King clone.
             ********************************************************/
            std::unique_ptr<Piece> ClonePiece() const override;

            /************************************************************************************************************
             * @brief Calculates all potential positions that are 1 step away from the king in the 8 adjacent directions.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The king's current position.
             * @param board The current board state.
             * @param directions The set of directions to check.
             * @return A vector of valid destination positions.
             ***********************************************************************************************************/
            std::vector<Position> GetPositionsFromAdjacentDirs(
                const Position &from_position, const Board &board, const std::vector<Direction> &directions) const;

            /**********************************************************************************
             * @brief Calculates potential positions for king side and queen side castling.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The king's current position.
             * @param board The current board state.
             * @return A vector of valid destination positions for castling moves.
             *********************************************************************************/
            std::vector<Position> GetPositionsFromCastling(
                const Position &from_position, const Board &board) const;

            /**********************************************************************************************
             * @brief Checks conditions to determine if a castling move is possible.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param king_position The king's starting position.
             * @param rook_position The rook's starting position.
             * @param positions_in_between A list of positions that must be empty for castling to be valid.
             * @param board The current board state.
             * @return true if the basic conditions for castling are met, false otherwise.
             *********************************************************************************************/
            bool CanCastle(
                const Position &king_position, const Position &rook_position,
                const std::vector<Position> &positions_in_between, const Board &board) const;

            /******************************************************************************************************************
             * @brief Calculates all potential adjacent and castling moves the King can make from a given position.
             *
             * For each adjacent position: if on board and (empty or enemy) include. Castling positions are also included here.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The starting position of the King
             * @param board The current state of the board for validation.
             * @param last_move Optional pointer to the last move made in the game (not typically used by King).
             * @return A vector of potential Move objects.
             *****************************************************************************************************************/
            std::vector<Move> GetPotentialMoves(
                const Position &from_position, const Board &board, const Move* last_move = nullptr) const override;

            /** @brief Static constant vector defining the 8 adjacent directions a King can move in. */
            static inline const std::vector<Direction> AdjacentDirs =
            {
                Direction::North,
                Direction::South,
                Direction::East,
                Direction::West,
                Direction::NorthEast,
                Direction::NorthWest,
                Direction::SouthEast,
                Direction::SouthWest
            };
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_BISHOP_HPP
#define GAMELOGIC_BISHOP_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    /***************************************************************************
     * @class Bishop
     * @brief Represents a Bishop chess piece.
     *
     * Inherits from the abstract base class `Piece` and implements the specific
     * movement logic for a Bishop (diagonal movement).
     ***************************************************************************/

    class Bishop: public Piece
    {
        public:
            /**********************************************************
             * @brief Constructs a Bishop Object with a specific color.
             * @param color The color (Light or Dark) of the Bishop.
             *********************************************************/
            Bishop(Enums::Color color);

            /** @brief  Virtual Default Destructor*/
            ~Bishop() override = default;

            /***********************************************************
             * @brief Creates a deep copy (clone) of this Bishop object.
             * @return A unique_ptr to the newly created Bishop clone.
             **********************************************************/
            std::unique_ptr<Piece> ClonePiece() const override;

            /***************************************************************************************************************************
             * @brief Calculates all potential diagonal moves the bishop can make from a given position.
             *
             * For each diagonal position: if on board and (empty or enemy) include.
             *
             * !!! IMPORTANT: This method does not check for King safety
             *
             * @param from_position The starting position of the Bishop.
             * @param board The current state of the board for validation.
             * @param last_move Optional pointer to the last move made in the game (not typically used by Bishops).
             * @return A vector of potential Move objects.
             **************************************************************************************************************************/
            std::vector<Move> GetPotentialMoves(
                const Position &from_position, const Board &board, const Move* last_move = nullptr) const override;

            /** @brief Static constant vector defining the four diagonal directions a Bishop can move in. */
            static inline const std::vector<Direction> DiagonalDirs =
                {
                    Direction::NorthEast,
                    Direction::NorthWest,
                    Direction::SouthEast,
                    Direction::SouthWest
                };
    };
} // namespace GameLogic

#endif
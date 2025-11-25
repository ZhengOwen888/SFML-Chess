#ifndef GAMELOGIC_KNIGHT_HPP
#define GAMELOGIC_KNIGHT_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Knight: public Piece
    {
        public:
            /**********************************************************
             * @brief Constructs a Knight Object with a specific color.
             * @param color The color (Light or Dark) of the Knight.
             *********************************************************/
            Knight(Enums::Color color);

            /** @brief  Virtual Default Destructor*/
            ~Knight() override = default;

            /***********************************************************
             * @brief Creates a deep copy (clone) of this Knight object.
             * @return A unique_ptr to the newly created Knight clone.
             **********************************************************/
            std::unique_ptr<Piece> ClonePiece() const override;

            /*******************************************************************
             * @brief Calculates all potential positions the Knight can jump to.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The knight's current position.
             * @param board The current board state.
             * @param directions The set of directions to check.
             * @return A vector of valid destination positions.
             ******************************************************************/
            std::vector<Position> GetPositionsFromJumpDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;

            /*****************************************************************************************************
             * @brief Calculates all potential jump moes the Knight can make from a given position.
             *
             * For each jump position: if on board and (empty or enemy) include.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The starting position of the Knight
             * @param board The current state of the board for validation.
             * @param last_move Optional pointer to the last move made in the game (not typically used by Knight).
             * @return A vector of potential Move objects.
             ****************************************************************************************************/
            std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const override;

            /** @brief Static constant vector defining the 8 jump directions a Knight can jump in. */
            static inline const std::vector<Direction> JumpDirs =
            {
                // North side jump
                Direction(-2, -1),
                Direction(-2,  1),

                // South side jump
                Direction( 2, -1),
                Direction( 2,  1),

                // West side jump
                Direction(-1, -2),
                Direction( 1, -2),

                // East side jump
                Direction(-1,  2),
                Direction( 1,  2)
            };
    };
} // namespace GameLogic

#endif
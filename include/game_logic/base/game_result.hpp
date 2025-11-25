#ifndef GAMELOGIC_RESULT_HPP
#define GAMELOGIC_RESULT_HPP

#include "game_logic/enums.hpp"

namespace GameLogic
{
    /*********************************************************************************************
     * @class GameResult
     * @brief Stores the final outcome and state of a chess game.
     *
     * This class determines if the game is still ongoing, a draw, or a win for a specific player,
     * and holds the reason for the game state (e.g., checkmate, stalemate, 50-move rule).
     ********************************************************************************************/
    class GameResult
    {
        public:
            /** @brief default Constructor, initialize GameState(Color::None, GameState::Ongoing) */
            GameResult();

            /** ************************************************************************
             * @brief Constructs a GameState object with player color and game state.
             * @param player_color color of the player.
             * @param game_state the state of the game during the current player's turn.
             **************************************************************************/
            GameResult(Enums::Color player_color, Enums::GameState game_state);

            /** @brief default Destructor */
            ~GameResult() = default;

            /** *****************************************************************************
             * @brief Set the game state to a win by checkmate by the winning player's color.
             * @param player_color color of the player.
             *******************************************************************************/
            void SetWin(Enums::Color winner_color);

            /** *****************************************************
             * @brief Set the game state to a draw with a reason.
             * @param game_state The reason the game ended in a draw.
             *
             * Applicable Reasons
             *  1. Stalemate
             *  2. ThreeFoldRepetition
             *. 3. FiftyMoveRule
             *  4. InsufficientMaterial
             *******************************************************/
            void SetDraw(Enums::GameState game_state);

            /******************************************************************
             * @brief Check if game is still in progress.
             * @return true if the game is GameState::Ongoing, false otherwise.
             *****************************************************************/
            bool IsOngoing() const;

        private:
            /** @brief The color associated with the final game state (Win: (Light, Dark), Draw : None) */
            Enums::Color player_color_;

            /** @brief  The specific outcome of the game. */
            Enums::GameState game_state_;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_RESULT_HPP
#define GAMELOGIC_RESULT_HPP

#include "game_logic/enums.hpp"

namespace GameLogic
{
    class GameResult
    {
        public:
            // Default constructor for ongoing game
            GameResult();
            // Construct a Result object which contain info on the state of the game
            GameResult(Enums::Color player_color, Enums::GameState game_state);

            ~GameResult() = default;

            // A player won by checkmate
            void SetWin(Enums::Color winner_color);

            // Both player ends up with a draw
            // 1. Stalemate
            // 2. ThreeFoldRepetition
            // 3. FiftyMoveRule
            // 4. InsufficientMaterial
            void SetDraw(Enums::GameState game_state);

            // Returns true if the game is still ongoing
            bool IsOngoing() const;

        private:
            Enums::Color player_color_;
            Enums::GameState game_state_;
    };
} // namespace GameLogic

#endif
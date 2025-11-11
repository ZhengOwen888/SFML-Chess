#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "board.hpp"
#include "player.hpp"

namespace GameLogic
{
    class Game
    {
        public:
            // Construct a Game object
            Game();
            ~Game();

            // Return the color of the current player
            const Player &GetCurrentPlayer() const;

            // Return the color of the current player's opponent's color
            const Player &GetOpponentPlayer() const;

        private:
            Board board_;
            Player player_light_;
            Player player_dark_;
            Enums::Color current_player_color_;
    };
}

#endif
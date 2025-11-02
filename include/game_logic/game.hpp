#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "board.hpp"
#include "player.hpp"

namespace GameLogic
{
    class Game
    {
        public:
            Game();
            ~Game();

            const Player &getCurrentPlayer() const;
            const Player &getOpponentPlayer() const;

        private:
            Board board_;
            Player player_light_;
            Player player_dark_;
            Enums::Color current_player_color_;
    };
}

#endif
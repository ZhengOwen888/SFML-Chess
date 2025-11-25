#ifndef GAMELOGIC_PLAYER_HEADER
#define GAMELOGIC_PLAYER_HEADER

#include "game_logic/enums.hpp"

namespace GameLogic
{
    class Player
    {
        public:
            // Contruct a Player object with color
            Player(Enums::Color color);
            ~Player() = default;

            // Return the color of this player
            Enums::Color GetColor() const;

        private:
            Enums::Color color_;
    };
} // namespace GameLogic

#endif
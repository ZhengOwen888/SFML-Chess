#ifndef GAMELOGIC_PLAYER_HEADER
#define GAMELOGIC_PLAYER_HEADER

#include "enums.hpp"

namespace GameLogic
{
    class Player
    {
        public:
            // contruct a Player object with color
            Player(Enums::Color color);
            ~Player();

            // return the color of this player
            Enums::Color GetColor() const;

            // Use this with caution
            void SetColor(Enums::Color color);

        private:
            Enums::Color color_;
    };
} // namespace GameLogic

#endif
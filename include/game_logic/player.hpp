#ifndef GAMELOGIC_PLAYER_HEADER
#define GAMELOGIC_PLAYER_HEADER

#include "enums.hpp"

namespace GameLogic
{
    class Player
    {
        public:
            Player(Enums::Color color);
            ~Player();

            // Get own player color
            Enums::Color getColor() const;

            // Use this with caution
            void setColor(Enums::Color color);

        private:
            Enums::Color color_;
    };
} // namespace GameLogic

#endif
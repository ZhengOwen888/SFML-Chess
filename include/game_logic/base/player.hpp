#ifndef GAMELOGIC_PLAYER_HEADER
#define GAMELOGIC_PLAYER_HEADER

#include "game_logic/enums.hpp"

namespace GameLogic
{
    /*************************************************************************************************
     * @class Player
     * @brief Represents one of the two participants in a chess game.
     *
     * The Player class mainly holds the color identifier (Light or Dark)
     * and can be expanded later to hold statistics, names, UI state, or Chess Engine if there is time.
     *************************************************************************************************/
    class Player
    {
        public:
            /*********************************************************************
             * @brief Constructs a Player object, assigning them a specific color.
             * @param color The color (side) of the player (Light or Dark).
             ********************************************************************/
            Player(Enums::Color color);

            /** @brief Default Destructor */
            ~Player() = default;

            /*********************************************
             * @brief Get the side of the player.
             * @return The color the player is playing as.
             ********************************************/
            Enums::Color GetColor() const;

        private:
            /** @brief The color the player if playing as. */
            Enums::Color color_;
    };
} // namespace GameLogic

#endif
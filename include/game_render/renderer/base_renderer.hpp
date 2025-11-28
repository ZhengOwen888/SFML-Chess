#ifndef GAMERENDER_BASE_RENDERER_HPP
#define GAMERENDER_BASE_RENDERER_HPP

#include "game_logic/game.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GameRender
{
    /*************************************************************************
     * @class BaseRenderer
     * @brief An abstract base class for all rendering components in the game.
     *
     * Defines a common interface that concrete renderers (BoardRenderer,
     * HighlightRenderer,...)
     ************************************************************************/
    class BaseRenderer
    {
        public:
            /** @brief Virtual destructor to ensure correct cleanup of derived classes */
            virtual ~BaseRenderer() = default;

            /*************************************************************************************
             * @brief Pure virtual function to render specific component or element on the window.
             *
             * This function must be implemented by all derived classes to perform
             * their specific drawing tasks.
             *
             * @param window A const reference to the active SFML render window.
             * @param game A const rederence to the current state of the game logic.
             ************************************************************************************/
            virtual void Render(sf::RenderWindow &window, const GameLogic::Game &game) = 0;
    };
} // namespace GameRender

#endif
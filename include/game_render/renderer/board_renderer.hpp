#ifndef GAMERENDER_BOARD_RENDERER_HPP
#define GAMERENDER_BOARD_RENDERER_HPP

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/base_renderer.hpp"

#include "game_logic/game.hpp"
#include "game_logic/base/position.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GameRender
{
    /****************************************************************************************
     * @class BoardRenderer
     * @brief Renders the physical chessboard and all pieces on it.
     *
     * Handles view scaling, flipping the perspective, and positioning of all board elements.
     ***************************************************************************************/
    class BoardRenderer : public BaseRenderer
    {
        public:
            /*********************************************************************************************************
             * @brief Construct a Board Renderer with a Asset Manager object.
             * @param asset_manager The Asset Manager object that will help load the textures of the board and pieces.
             ********************************************************************************************************/
            BoardRenderer(AssetManager& asset_manager);

            /** @brief Default Destructor */
            ~BoardRenderer() override = default;

            /**************************************************************************************************************
             * @brief Render the sprite of the board and the pieces onto the window based on the current state of the game.
             * @param window A reference to the window where we will draw the sprite of the board and pieces.
             * @param game A const reference to to the current game object for reading the state of the game.
             *************************************************************************************************************/
            void Render(sf::RenderWindow &window, const GameLogic::Game &game) override;

            /*********************************************************************************
             * @brief Update the SFML View so that the board scales correctly with the window.
             * @param window A reference to the window in which we will update the view.
             ********************************************************************************/
            void UpdateView(sf::RenderWindow &window);

            /*************************************************************************************
             * @brief Toggles the perspective of the board depening on which side is being played.
             * @param play_as_black A flag when true, flips the board to black's viewpoint.
             ************************************************************************************/
            void TogglePerspective(bool play_as_black);

        private:
            /** @brief Reference to the application's Asset Manager for retrieving textures for the board and pieces. */
            AssetManager &asset_manager_;

            /** @brief Flag indicating whether the board should be flipped to black's perspective. */
            bool playing_as_black_;

            /** @brief The Calculated pixel size of a single square on the board. */
            float square_size_;

            /** @brief The base pixel dimensions for the size of the board's width and height. */
            const sf::Vector2f board_size_;

            /** @brief The whole view or world of the window. */
            sf::View view_;

            /**************************************************************************
             * @brief Calculate the the center of the view based on the current window.
             * @param window A const reference to the current window.
             * @return A sf::Vector2f representing the center position of the view.
             *************************************************************************/
            sf::Vector2f GetViewCenter(const sf::RenderWindow &window) const;

            /***************************************************************************************************
             * @brief Converts chess coordinates (0-7) into screen pixel coordinates for the center of a square.
             * @param row The 0 based row index.
             * @param col The 0 based column index.
             * @return The SFML pixel position of the center of the square (sf::Vector2f).
             **************************************************************************************************/
            sf::Vector2f GetSquareCenter(int row, int col);

            /************************************************************************************
             * @brief Draws the board background on the window (creats a local sprite).
             * @param window A reference to the window that the board sprite will be rendered on.
             ***********************************************************************************/
            void DrawBoard(sf::RenderWindow &window);

            /*************************************************************************************************
             * @brief Draws all active pieces on the board at their correct locations (creates local sprites).
             * @param window A reference to the window that the piece sprites will be rendered on.
             * @param pieces A map of all current pieces from the game state.
             ************************************************************************************************/
            void DrawPieces(sf::RenderWindow &window, const std::map<GameLogic::Position, const GameLogic::Piece *> pieces);
    };
} // namespace GameRender

#endif
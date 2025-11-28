#ifndef GAMERENDER_BOARD_RENDERER_HPP
#define GAMERENDER_BOARD_RENDERER_HPP

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/base_renderer.hpp"
#include "game_render/renderer/highlight_renderer.hpp"

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

            /***************************************************************************************************************************************************************
             * @brief Set the positions that we need to highlight based on the position the user clicked on.
             * @param selected_position A const reference to the position that the user clicked on.
             * @param selected_position_color A const reference to a sf::Color that will be used to highlight the selected position.
             * @param positions_to_highlight_with_colors A const reference to the possible positions the player can move their selected piece to and their highlight colors.
             **************************************************************************************************************************************************************/
            void SetPositionsToHighlight(
                const GameLogic::Position &selected_position,
                const sf::Color &selected_position_color,
                const std::map<GameLogic::Position, sf::Color> &positions_to_highlight_with_colors
            );

            /*********************************************************************************
             * @brief Set the current theme for pieces then load their textures.
             * @param theme The theme that is to be loaded for the pieces.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadPieceTheme(Enums::Theme theme);

            /*********************************************************************************
             * @brief Set the current theme for board then load its texture.
             * @param theme The theme that is to be loaded for the board.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadBoardTheme(Enums::Theme theme);

            /******************************************************************
             * @brief Get the that contains the board and pieces.
             * @return A sf::View representing the center position of the view.
             *****************************************************************/
            sf::View GetView();

        private:
            /** @brief Reference to the application's Asset Manager for retrieving textures for the board and pieces. */
            AssetManager &asset_manager_;

            /** @brief The renderer that will render the indicators for possible moves and more.  */
            HighlightRenderer highlight_renderer_;

            /** @brief Flag indicating whether the board should be flipped to black's perspective. */
            bool playing_as_black_;

            /** @brief The Calculated pixel size of a single square on the board. */
            float square_size_;

            /** @brief The base pixel dimensions for the size of the board's width and height. */
            const sf::Vector2f board_size_;

            /** @brief The whole view or world of the window. */
            sf::View view_;

            /***************************************************************************************************
             * @brief Converts chess coordinates (0-7) into screen pixel coordinates for the center of a square.
             * @param col The 0 based column index.
             * @param row The 0 based row index.
             * @return The SFML pixel position of the center of the square (sf::Vector2f).
             **************************************************************************************************/
            sf::Vector2f GetSquareCenter(int col, int row);

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
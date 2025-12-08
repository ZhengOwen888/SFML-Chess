#ifndef GAMERENDERER_HIGHLIGHT_RENDERER_HPP
#define GAMERENDERER_HIGHLIGHT_RENDERER_HPP

#include "game_logic/base/position.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

namespace GameRender
{
    /*********************************************************************************
     * @class HighlightRenderer
     * @brief Renders the indicators that are useful for hinting what moves are legal.
     *
     * Handles highlighting squares for visual effects.
     ********************************************************************************/
    class HighlightRenderer
    {
        public:
            /**************************************************************************************************************************************
             * @brief  Construct a HighlightRenderer object with the size of a square on the board and a flag to signal perspective change.
             * @param square_size The size of the width and height of a single square on the board.
             * @param playing_as_black A flag that signals the player will be playing in black's perspective and will affect position calculations.
             *************************************************************************************************************************************/
            HighlightRenderer(float square_size, bool playing_as_black);

            /** @brief Default Destructor. */
            ~HighlightRenderer() = default;

            /***************************************************************************************************
             * @brief Render the indicator of highlighting for possible move hinting, illegal moves, and others.
             * @param window A reference to the window where we will do the rendering.
             **************************************************************************************************/
            void Render(sf::RenderWindow &window);

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

            /************************************************************************************
             * @brief Set the flag which signals if the player is playing in black's perspective.
             * @param play_as_black The flag that represents if the player is playing as black.
             ***********************************************************************************/
            void SetPlayingAsBlack(bool play_as_black);

        private:
            /** @brief The position that the user clicked on or selected. */
            GameLogic::Position selected_position_;

            /** @brief The color that will be used to highlight the selected position. */
            sf::Color selected_position_color_;

            /** @brief The possible positions that the piece the player selected can move to and be highlighted by a specified color. */
            std::map<GameLogic::Position, sf::Color> positions_to_highlight_with_colors_;

            /** @brief The size of the width and height of each square on the board. */
            float square_size_;

            /** @brief A flag that signals the player is playing in black's perspective. */
            bool playing_as_black_;

            /*************************************************************************************************************
             * @brief Calculate the position of the top left corner of a square for the window.
             * @param col The 0 based column index.
             * @param row The 0 based row index.
             * @return A sf::Vector2f of the x and y position where the top left corner of the square will be on the board.
             *************************************************************************************************************/
            sf::Vector2f GetSquareTopLeftCorner(int col, int row);

            /*********************************************************************************************************************
             * @brief A Helper for highlighting a square on the board, which gets a highlighted and positioned square to be drawn.
             * @param position A const reference to a position that needs to be highlighted.
             * @param color A const reference to sf::Color, which is the color of the highlighted square.
             ********************************************************************************************************************/
            sf::RectangleShape GetHighlightedSquare(const GameLogic::Position &position, const sf::Color &color);

            /****************************************************************************
             * @brief Highlight the the position that the player selected.
             * @param window A reference to the window where we will do the highlighting.
             * @param highlight_color A sf::Color the highlight will use.
             ***************************************************************************/
            void HighlightSelectedPosition(sf::RenderWindow &window);

            /**************************************************************************************
             * @brief Highlight the possible positions the player can move their selected piece to.
             * @param window A reference to the window where we will do the highlighting.
             * @param highlight_color A sf::Color the highlight will use.
             *************************************************************************************/
            void HighlightPossibleMoves(sf::RenderWindow &window);

            /************************************************************************************
             * @brief Checks if the position is valid based on the dimensions of the chess board.
             * @param col The col index (0 based).
             * @param row The row index (0 based).
             ***********************************************************************************/
            bool IsValidPosition(int col, int row);
    };
} // namespace GameRender

#endif
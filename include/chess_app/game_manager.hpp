#ifndef CHESSAPP_GAMEMANAGER_HPP
#define CHESSAPP_GAMEMANAGER_HPP

#include "game_logic/game.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/board_renderer.hpp"
#include "game_render/renderer/highlight_renderer.hpp"

#include "chess_app/uci_handler.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <optional>
#include <algorithm>
#include <tuple>
#include <map>

namespace ChessApp
{
    /****************************************************************************************
     * @class GameManager
     * @brief Orchestrates the main application loop, input handling, and game state display.
     *
     * This class manages the interaction between the SFML UI layer and the
     * GameLogic layer, using a BoardRenderer to visualize the game state.
     ***************************************************************************************/
    class GameManager
    {
        public:
            /** @brief Constructs a new GameManager object and initialize the board renderer and the window. */
            GameManager();

            /** @brief Default Destructor for GameManager. */
            ~GameManager() = default;

            /** @brief Starts the main application loop. */
            void Run();

            /*********************************************************************************
             * @brief Set the current theme for pieces then load their textures.
             * @param theme The theme that is to be loaded for the pieces.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadPieceTheme(GameRender::Enums::Theme theme);

            /*********************************************************************************
             * @brief Set the current theme for board then load its texture.
             * @param theme The theme that is to be loaded for the board.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadBoardTheme(GameRender::Enums::Theme theme);

        private:
            sf::RenderWindow window_;

            GameLogic::Game game_;
            GameRender::AssetManager asset_manager_;
            GameRender::BoardRenderer board_renderer_;

            ChessApp::UCIHandler uci_handler_;

            std::optional<GameLogic::Position> selected_position_;
            std::map<GameLogic::Position, sf::Color> current_legal_positions_with_colors_;
            std::vector<GameLogic::Move> current_legal_moves_;

            bool playing_as_black_;

            void HandleEvent(const sf::Event& event);

            void HandleWindowCloseEvent();

            void HandleWindowResizeEvent();

            void HandleClickOnBoardEvent(sf::Vector2f world_pos);

            // -- Helpers to Handle Piece Selection and Move Attempt -- //

            void HandleMoveAttempt(GameLogic::Position clicked_position);

            void HandlePieceSelection(GameLogic::Position clicked_position);

            void ExecuteAIMove();

            void TryExecuteAIMove();

            void UpdateHighlight(GameLogic::Position selected_position, sf::Color highlight_color);

            void ClearSelectionState();

            void HandleSwitchColor();

            // -- Rendering Helpers
            void Render();

            void Display();
    };
} // namespace ChessApp

#endif
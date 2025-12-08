#ifndef CHESSAPP_GAMEMANAGER_HPP
#define CHESSAPP_GAMEMANAGER_HPP

#include "game_logic/game.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/enums.hpp"

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
            GameLogic::Enums::Color ai_color_;

            // -- UI State -- //
            bool showing_promotion_dialog_ = false;
            GameLogic::Move pending_promotion_move_;
            bool showing_game_over_dialog_ = false;

            // -- UI Elements -- //
            sf::Font font_;
            bool font_loaded_ = false;

            // -- Button Rectangles -- //
            sf::FloatRect undo_button_rect_;
            sf::FloatRect redo_button_rect_;
            sf::FloatRect new_game_button_rect_;

            // -- Promotion Button Rectangles -- //
            sf::FloatRect queen_button_rect_;
            sf::FloatRect rook_button_rect_;
            sf::FloatRect bishop_button_rect_;
            sf::FloatRect knight_button_rect_;

            void HandleEvent(const sf::Event& event);

            void HandleWindowCloseEvent();

            void HandleWindowResizeEvent();

            void HandleClickOnBoardEvent(sf::Vector2f world_pos);

            void HandleUIClick(sf::Vector2i pixel_pos);

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

            // -- UI Rendering -- //
            void RenderUI();

            void RenderButtons();

            void RenderPromotionDialog();

            void RenderGameOverDialog();

            // -- UI Button Helpers -- //
            void DrawButton(const sf::FloatRect& rect, const std::string& text, bool enabled = true);

            bool IsPointInRect(sf::Vector2f point, const sf::FloatRect& rect);

            // -- Promotion Handling -- //
            void ShowPromotionDialog(const GameLogic::Move& move);

            void HandlePromotionChoice(GameLogic::Enums::PieceType type);

            // -- Game State Helpers -- //
            void CheckGameOver();
    };
} // namespace ChessApp

#endif
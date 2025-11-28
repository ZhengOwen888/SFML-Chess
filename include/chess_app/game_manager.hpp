#ifndef CHESSAPP_GAMEMANAGER_HPP
#define CHESSAPP_GAMEMANAGER_HPP

#include "game_logic/game.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/board_renderer.hpp"
#include "game_render/renderer/highlight_renderer.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <optional>
#include <algorithm>

namespace ChessApp
{
    class GameManager
    {
        public:
            GameManager();
            ~GameManager() = default;

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
            GameLogic::Game game_;
            GameRender::BoardRenderer board_renderer_;

            sf::RenderWindow window_;

            std::optional<GameLogic::Position> selected_position_state_;
            std::map<GameLogic::Position, sf::Color> current_legal_positions_with_colors_;
            std::vector<GameLogic::Move> current_legal_moves_;

            void HandleEvent(const sf::Event& event);

            void HandleWindowCloseEvent();

            void HandleWindowResizeEvent();

            void HandleClickOnBoardEvent(sf::Vector2f world_pos);

            void Render();

            void Display();
    };
} // namespace ChessApp

#endif
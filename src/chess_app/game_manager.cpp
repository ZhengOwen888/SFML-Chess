#include "chess_app/game_manager.hpp"

#include "game_logic/game.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/board_renderer.hpp"
#include "game_render/renderer/highlight_renderer.hpp"
#include "game_render/constants.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <optional>
#include <algorithm>

namespace ChessApp
{
    GameManager::GameManager()
        : game_(GameLogic::Game()),
        board_renderer_(*GameRender::AssetManager::GetInstance()),
        window_(sf::VideoMode({800, 800}), "SFML_CHESS", sf::Style::Default),
        selected_position_state_(std::nullopt)
    {};

    void GameManager::Run()
    {
        while (this->window_.isOpen())
        {
            while (const std::optional<sf::Event> event = this->window_.pollEvent())
            {
                HandleEvent(*event);
            }

            Render();
            Display();
        }
    }

    void GameManager::HandleEvent(const sf::Event &event)
    {
        if (event.is<sf::Event::Closed>())
        {
            HandleWindowCloseEvent();
        }
        else if (event.is<sf::Event::Resized>())
        {
            HandleWindowResizeEvent();
        }
        else if (event.is<sf::Event::MouseButtonPressed>())
        {
            const auto *mouse_clicked_event = event.getIf<sf::Event::MouseButtonPressed>();

            if (mouse_clicked_event->button == sf::Mouse::Button::Right)
            {
                return;
            }

            sf::Vector2i pixel_pos{mouse_clicked_event->position};

            // this->window_.setView(menu_renderer.GetView());

            // if (this->menu_render_.CheclClick(pixel_pos))
            // {
            //      do something
            //      return;
            // }

            this->window_.setView(this->board_renderer_.GetView());
            sf::Vector2f world_pos = this->window_.mapPixelToCoords(pixel_pos);

            HandleClickOnBoardEvent(world_pos);
        }
    }

    void GameManager::HandleWindowCloseEvent()
    {
        this->window_.close();
    }

    void GameManager::HandleWindowResizeEvent()
    {
        this->board_renderer_.UpdateView(this->window_);
    }

    void GameManager::HandleClickOnBoardEvent(sf::Vector2f world_pos)
    {
        int col = static_cast<int>(world_pos.x / GameRender::Constants::SQUARE_SIZE);
        int row = static_cast<int>(world_pos.y / GameRender::Constants::SQUARE_SIZE);



        GameLogic::Position clicked_position{row, col};

        if (this->selected_position_state_.has_value())
        {
            auto it = std::find(this->current_legal_positions_.begin(), this->current_legal_positions_.end(), clicked_position);

            if (it != this->current_legal_positions_.end())
            {
                const auto legal_moves = this->game_.GetLegalMovesAtPosition(this->selected_position_state_.value());

                for (const auto& move : legal_moves)
                {
                    if (move.GetToPosition() == clicked_position)
                    {
                        this->game_.ExecuteMove(move);
                        break;
                    }
                }
            }

            this->selected_position_state_ = std::nullopt;
            this->current_legal_positions_.clear();
            this->board_renderer_.SetPositionsToHighlight(GameLogic::Position{-1, -1}, {});
            return;
        }

        const auto legal_moves = this->game_.GetLegalMovesAtPosition(clicked_position);

        if (!legal_moves.empty())
        {
            this->selected_position_state_ = std::make_optional(clicked_position);
            this->current_legal_positions_.clear();
            for (const auto &move : legal_moves)
            {
                this->current_legal_positions_.push_back(move.GetToPosition());
            }
            this->board_renderer_.SetPositionsToHighlight(this->selected_position_state_.value(), this->current_legal_positions_);
        }
        else
        {
            this->selected_position_state_ = std::nullopt;
            this->current_legal_positions_.clear();
            this->board_renderer_.SetPositionsToHighlight(GameLogic::Position{-1, -1}, {});
        }
    }

    void GameManager::Render()
    {
        this->board_renderer_.Render(this->window_, this->game_);
    }

    void GameManager::Display()
    {
        this->window_.display();
    }

    bool GameManager::SetAndLoadPieceTheme(GameRender::Enums::Theme theme)
    {
        return this->board_renderer_.SetAndLoadPieceTheme(theme);
    }

    bool GameManager::SetAndLoadBoardTheme(GameRender::Enums::Theme theme)
    {
        return this->board_renderer_.SetAndLoadBoardTheme(theme);
    }
} // namespace ChessApp
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
        selected_position_(std::nullopt)
    {};

    void GameManager::Run()
    {
        while (this->window_.isOpen())
        {
            this->window_.clear(sf::Color::Black);

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
            //      do something // this will be used for the menu later probably if we have time.
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

        if (this->selected_position_.has_value())
        {
            HandleMoveAttempt(clicked_position);
        }
        else
        {
            HandlePieceSelection(clicked_position);
        }
    }

    void GameManager::HandleMoveAttempt(GameLogic::Position clicked_position)
    {
        auto valid_move = std::find_if(
            this->current_legal_moves_.begin(),
            this->current_legal_moves_.end(),
            [&](const auto &move) { return move.GetToPosition() == clicked_position; });

        if (valid_move != this->current_legal_moves_.end())
        {
            ClearSelectionState();
            UpdateHighlight(clicked_position, GameRender::Constants::SUCCESS_MOVE_GOLD);
            this->game_.ExecuteMove(*valid_move);
        }
        else
        {
            ClearSelectionState();
            UpdateHighlight(clicked_position, GameRender::Constants::INVALID_MOVE_RED);
        }
    }

    void GameManager::HandlePieceSelection(GameLogic::Position clicked_position)
    {
        ClearSelectionState();
        this->board_renderer_.SetPositionsToHighlight(GameLogic::Position{-1, -1}, sf::Color::Transparent, {});

        this->selected_position_ = clicked_position;
        this->current_legal_moves_ = this->game_.GetLegalMovesAtPosition(clicked_position);

        if (!this->current_legal_moves_.empty())
        {
            for (const auto& move : this->current_legal_moves_)
            {
                this->current_legal_positions_with_colors_.insert(
                    {move.GetToPosition(), GameRender::Constants::MOVE_HIGHLIGHT_GREEN}
                );
            }
            UpdateHighlight(this->selected_position_.value(), GameRender::Constants::MOVE_HIGHLIGHT_GREEN);
        }
        else
        {
            UpdateHighlight(this->selected_position_.value(), GameRender::Constants::INVALID_MOVE_RED);
            ClearSelectionState();
        }
    }

    void GameManager::UpdateHighlight(GameLogic::Position selected_position, sf::Color highlight_color)
    {
        this->board_renderer_.SetPositionsToHighlight(
            selected_position,
            highlight_color,
            this->current_legal_positions_with_colors_
        );
    }

    void GameManager::ClearSelectionState()
    {
        this->selected_position_ = std::nullopt;
        this->current_legal_moves_.clear();
        this->current_legal_positions_with_colors_.clear();
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


// if (this->selected_position_state_.has_value())
//         {
//             this->board_renderer_.SetPositionsToHighlight(
//                 clicked_position,
//                 sf::Color(255, 0, 0, 150),
//                 {}
//             );

//             for (const auto& move : this->current_legal_moves_)
//             {
//                 if (move.GetToPosition() == clicked_position)
//                 {
//                     this->board_renderer_.SetPositionsToHighlight(
//                         clicked_position,
//                         sf::Color(218, 165, 32, 128),
//                         {}
//                     );
//                     this->game_.ExecuteMove(move);
//                     break;
//                 }
//             }

//             this->selected_position_state_ = std::nullopt;
//             this->current_legal_positions_with_colors_.clear();
//             this->current_legal_moves_.clear();
//             return;
//         }

//         this->current_legal_moves_ = this->game_.GetLegalMovesAtPosition(clicked_position);

//         if (!this->current_legal_moves_.empty())
//         {
//             this->selected_position_state_ = std::make_optional(clicked_position);
//             this->current_legal_positions_with_colors_.clear();
//             for (const auto &move : this->current_legal_moves_)
//             {
//                 this->current_legal_positions_with_colors_.insert({move.GetToPosition(), sf::Color(118, 150, 86, 128)});
//             }
//             this->board_renderer_.SetPositionsToHighlight(
//                 this->selected_position_state_.value(),
//                 sf::Color(118, 150, 86, 128),
//                 this->current_legal_positions_with_colors_
//             );
//         }
//         else
//         {
//             this->board_renderer_.SetPositionsToHighlight(
//                 clicked_position,
//                 sf::Color(255, 0, 0, 150),
//                 {}
//             );
//             this->selected_position_state_ = std::nullopt;
//             this->current_legal_positions_with_colors_.clear();
//         }
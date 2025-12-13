#include "chess_app/game_manager.hpp"

#include "game_logic/game.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/board_renderer.hpp"
#include "game_render/renderer/highlight_renderer.hpp"
#include "game_render/constants.hpp"

#include "chess_app/uci_handler.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <tuple>
#include <map>

namespace ChessApp
{
    GameManager::GameManager()
        : game_(GameLogic::Game()),
        asset_manager_(),
        board_renderer_(&asset_manager_),
        uci_handler_("./stockfish"),
        window_(sf::VideoMode(
            {static_cast<unsigned int>(GameRender::Constants::INITIAL_WINDOW_WIDTH), static_cast<unsigned int>(GameRender::Constants::INITIAL_WINDOW_HEIGHT)}),
            "SFML_CHESS", sf::Style::Default),
        selected_position_(std::nullopt),
        playing_as_black_(false),
        undo_button_rect_(sf::FloatRect{{10.f, 810.f}, {GameRender::Constants::BUTTON_WIDTH, GameRender::Constants::BUTTON_HEIGHT}}),
        redo_button_rect_(sf::FloatRect{{120.f, 810.f}, {GameRender::Constants::BUTTON_WIDTH, GameRender::Constants::BUTTON_HEIGHT}}),
        new_game_button_rect_(sf::FloatRect{{690.f, 810.f}, {GameRender::Constants::BUTTON_WIDTH, GameRender::Constants::BUTTON_HEIGHT}})
    {
        board_renderer_.UpdateView(window_);

        if (font_.openFromFile("./assets/fonts/MantiSans.ttf"))
        {
            font_loaded_ = true;
        }

        ai_color_ = playing_as_black_
                    ? GameLogic::Enums::Color::Light
                    : GameLogic::Enums::Color::Dark;
    };

    void GameManager::Run()
    {
        while (this->window_.isOpen())
        {
            while (const std::optional<sf::Event> event = this->window_.pollEvent())
            {
                HandleEvent(*event);
            }

            TryExecuteAIMove();

            window_.clear(sf::Color::Black);
            Render();
            RenderUI();
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

            // IMPORTANT: ensure we use the same view the renderer used for this frame
            // (BoardRenderer::UpdateView sets board_renderer_.GetView())
            window_.setView(this->board_renderer_.GetView());

            // Map pixel -> world coords using the board view (so UI and board use same coordinate space)
            sf::Vector2f world_pos = this->window_.mapPixelToCoords(pixel_pos);

            // If we're showing a dialog, interpret the click in the SAME world coords
            if (showing_promotion_dialog_ || showing_game_over_dialog_)
            {
                // Use pixel_pos only if your HandleUIClick expects raw pixels.
                // But we changed HandleUIClick below to accept world coords, so pass world_pos.
                HandleUIClick(pixel_pos);
                return;
            }

            // Otherwise this is a board click (world_pos already correct)
            HandleClickOnBoardEvent(world_pos);
        }

        else if (event.is<sf::Event::KeyPressed>())
        {
            const auto *key_event = event.getIf<sf::Event::KeyPressed>();

            // Keyboard shortcuts
            if (key_event->code == sf::Keyboard::Key::Z && key_event->control)
            {
                if (game_.CanUndo())
                {
                    game_.UnExecuteMove();
                    game_.UnExecuteMove();
                    ClearSelectionState();
                    showing_game_over_dialog_ = false;
                }
            }
            else if (key_event->code == sf::Keyboard::Key::Y && key_event->control)
            {
                if (game_.CanRedo())
                {
                    game_.ReExecuteMove();
                    game_.ReExecuteMove();
                    ClearSelectionState();
                    CheckGameOver();
                }
            }

            else if (key_event->code == sf::Keyboard::Key::N && key_event->control)
            {
                game_.Reset();
                ClearSelectionState();
                showing_game_over_dialog_ = false;
            }

            else if (key_event->code == sf::Keyboard::Key::T && key_event->control)
            {
                game_.Reset();
                ClearSelectionState();
                showing_game_over_dialog_ = false;
                HandleSwitchColor();
            }
        }
    }

    void GameManager::HandleWindowCloseEvent()
    {
        this->window_.close();
    }

    void GameManager::HandleWindowResizeEvent()
    {
        // AdjustWindowSize();
        this->board_renderer_.UpdateView(window_);
    }

    void GameManager::HandleClickOnBoardEvent(sf::Vector2f world_pos)
    {
        int col = static_cast<int>(world_pos.x / GameRender::Constants::SQUARE_SIZE);
        int row = static_cast<int>(world_pos.y / GameRender::Constants::SQUARE_SIZE);

        // Flip coordinates if playing as black
        if (playing_as_black_)
        {
            col = 7 - col;
            row = 7 - row;
        }


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
            [&](const auto &move) { return move.GetToPosition() == clicked_position; }
        );

        if (valid_move != this->current_legal_moves_.end())
        {
            // Check if it's a pawn promotion move
            if (valid_move->GetMoveType() == GameLogic::Enums::MoveType::PawnPromotion)
            {
                ShowPromotionDialog(*valid_move);
            }
            else
            {
                ClearSelectionState();
                UpdateHighlight(clicked_position, GameRender::Constants::SUCCESS_MOVE_GOLD);
                this->game_.ExecuteMove(*valid_move);
                CheckGameOver();
            }
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

    bool GameManager::IsPointInRect(sf::Vector2f point, const sf::FloatRect& rect)
    {
        return point.x >= rect.position.x && point.x <= rect.position.x + rect.size.x
            && point.y >= rect.position.y && point.y <= rect.position.y + rect.size.y;
    }

    void GameManager::HandleUIClick(sf::Vector2i pixel_pos)
    {
        // Convert pixel position to world coordinates using board view
        sf::Vector2f world_pos = window_.mapPixelToCoords(pixel_pos, board_renderer_.GetView());

        if (showing_promotion_dialog_)
        {
            sf::View boardView = board_renderer_.GetView();
            sf::Vector2f center = boardView.getCenter();

            float total_width = 4 * GameRender::Constants::PROMOTION_BUTTON_SIZE
                                + 3 * GameRender::Constants::PROMOTION_BUTTON_MARGIN;
            float start_x = center.x - total_width / 2.f;
            float button_y = center.y - GameRender::Constants::PROMOTION_BUTTON_SIZE / 2.f + 20.f;

            // Define rectangles for each promotion button
            sf::FloatRect queen_rect{{start_x, button_y},
                                    {GameRender::Constants::PROMOTION_BUTTON_SIZE,
                                    GameRender::Constants::PROMOTION_BUTTON_SIZE}};
            sf::FloatRect rook_rect{{start_x + 1 * (GameRender::Constants::PROMOTION_BUTTON_SIZE + GameRender::Constants::PROMOTION_BUTTON_MARGIN),
                                    button_y},
                                    {GameRender::Constants::PROMOTION_BUTTON_SIZE,
                                    GameRender::Constants::PROMOTION_BUTTON_SIZE}};
            sf::FloatRect bishop_rect{{start_x + 2 * (GameRender::Constants::PROMOTION_BUTTON_SIZE + GameRender::Constants::PROMOTION_BUTTON_MARGIN),
                                    button_y},
                                    {GameRender::Constants::PROMOTION_BUTTON_SIZE,
                                    GameRender::Constants::PROMOTION_BUTTON_SIZE}};
            sf::FloatRect knight_rect{{start_x + 3 * (GameRender::Constants::PROMOTION_BUTTON_SIZE + GameRender::Constants::PROMOTION_BUTTON_MARGIN),
                                    button_y},
                                    {GameRender::Constants::PROMOTION_BUTTON_SIZE,
                                    GameRender::Constants::PROMOTION_BUTTON_SIZE}};

            if (IsPointInRect(world_pos, queen_rect))
            {
                HandlePromotionChoice(GameLogic::Enums::PieceType::Queen);
                return;
            }
            if (IsPointInRect(world_pos, rook_rect))
            {
                HandlePromotionChoice(GameLogic::Enums::PieceType::Rook);
                return;
            }
            if (IsPointInRect(world_pos, bishop_rect))
            {
                HandlePromotionChoice(GameLogic::Enums::PieceType::Bishop);
                return;
            }
            if (IsPointInRect(world_pos, knight_rect))
            {
                HandlePromotionChoice(GameLogic::Enums::PieceType::Knight);
                return;
            }
            return;
        }

        // Game over dialog (optional: could also tie to board view if you want)
        if (showing_game_over_dialog_)
        {
            sf::View boardView = board_renderer_.GetView();
            sf::Vector2f center = boardView.getCenter();

            sf::FloatRect new_game_rect{{center.x - GameRender::Constants::BUTTON_WIDTH / 2.f,
                                        center.y + 20.f},
                                        {GameRender::Constants::BUTTON_WIDTH,
                                        GameRender::Constants::BUTTON_HEIGHT}};

            if (IsPointInRect(world_pos, new_game_rect))
            {
                game_.Reset();
                ClearSelectionState();
                showing_game_over_dialog_ = false;
                return;
            }
        }
    }



    void GameManager::HandlePromotionChoice(GameLogic::Enums::PieceType type)
    {
        showing_promotion_dialog_ = false;
        pending_promotion_move_.SetPromotionPieceType(type);
        game_.ExecuteMove(pending_promotion_move_);
        CheckGameOver();
    }

    void GameManager::ExecuteAIMove()
    {
        std::string fen_str = this->game_.GenerateFen();
        std::string uci_best_move = this->uci_handler_.GetBestMove(fen_str);
        auto [from_position, to_position, promotion_type] = GameLogic::Move::FromUCI(uci_best_move);

        std::cout << fen_str << "\n";
        std::cout << uci_best_move << "\n";

        auto ai_legal_moves = this->game_.GetLegalMovesAtPosition(from_position);

        std::cout << ai_legal_moves.size() << "\n";

        auto valid_move = std::find_if(
            ai_legal_moves.begin(),
            ai_legal_moves.end(),
            [&](const GameLogic::Move &move) { return move.GetToPosition() == to_position; }
        );

        if (valid_move != ai_legal_moves.end())
        {
            if (valid_move->GetMoveType() == GameLogic::Enums::MoveType::PawnPromotion)
            {
                valid_move->SetPromotionPieceType(promotion_type);
            }
            this->game_.ExecuteMove(*valid_move);
        }
        else
        {
            std::cout << "Board should have reset\n";
            this->game_.DisplayBoard();
            std::cout << "\nFrom Position: " << from_position.GetRow() << " " << from_position.GetCol() << "\n";
            std::cout << "  To Position: " << to_position.GetRow() << " " << to_position.GetCol() << "\n";
            throw std::runtime_error("Error: Engine made an illegal move.");
        }

        CheckGameOver();
    }

    void GameManager::TryExecuteAIMove()
    {
        GameLogic::Enums::Color current_player = this->game_.GetCurrentPlayer().GetColor();

        if (ai_color_ == current_player)
        {
            ExecuteAIMove();
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

    void GameManager::HandleSwitchColor()
    {
        this->playing_as_black_ = !this->playing_as_black_;
        this->board_renderer_.TogglePerspective(this->playing_as_black_);
        this-> ai_color_ = playing_as_black_
                        ? GameLogic::Enums::Color::Light
                        : GameLogic::Enums::Color::Dark;
        ClearSelectionState();
        current_legal_moves_.clear();
        current_legal_positions_with_colors_.clear();
    }

    void GameManager::ShowPromotionDialog(const GameLogic::Move& move)
    {
        pending_promotion_move_ = move;
        showing_promotion_dialog_ = true;
        ClearSelectionState();
    }

    void GameManager::CheckGameOver()
    {
        if (game_.IsGameOver())
        {
            showing_game_over_dialog_ = true;
        }
    }

    void GameManager::RenderButtons()
    {
        // Draw current player indicator
        if (font_loaded_)
        {
            std::string turn_text = (game_.GetCurrentPlayer().GetColor() == GameLogic::Enums::Color::Light)
                                    ? "White's Turn" : "Black's Turn";
            sf::Text turn_indicator(font_, turn_text, 20);
            turn_indicator.setFillColor(sf::Color::White);
            turn_indicator.setPosition({350.f, 815.f});
            window_.draw(turn_indicator);
        }
    }

    void GameManager::RenderUI()
    {

        window_.setView(this->board_renderer_.GetView());
        RenderButtons();

        if (showing_promotion_dialog_)
        {
            RenderPromotionDialog();
        }

        if (showing_game_over_dialog_)
        {
            RenderGameOverDialog();
        }
    }

    void GameManager::RenderPromotionDialog()
    {
        sf::View board_view = board_renderer_.GetView();
        sf::Vector2f center = board_view.getCenter();

        window_.setView(window_.getDefaultView());

        sf::RectangleShape overlay(sf::Vector2f{
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window_.draw(overlay);

        window_.setView(board_view);

        // Draw dialog background (centered on board)
        sf::RectangleShape dialog(sf::Vector2f{GameRender::Constants::DIALOG_WIDTH,
                                            GameRender::Constants::DIALOG_HEIGHT});
        dialog.setFillColor(GameRender::Constants::DIALOG_BG_COLOR);
        dialog.setOutlineColor(GameRender::Constants::DIALOG_BORDER_COLOR);
        dialog.setOutlineThickness(2.f);
        dialog.setPosition(sf::Vector2f{
            center.x - GameRender::Constants::DIALOG_WIDTH / 2.f,
            center.y - GameRender::Constants::DIALOG_HEIGHT / 2.f
        });
        window_.draw(dialog);

        // Draw title
        if (font_loaded_)
        {
            sf::Text title(font_, "Choose Promotion Piece", 24);
            title.setFillColor(sf::Color::White);
            sf::FloatRect title_bounds = title.getLocalBounds();
            title.setPosition(sf::Vector2f{
                center.x - title_bounds.size.x / 2.f,
                center.y - 80.f
            });
            window_.draw(title);
        }

        // Draw promotion buttons
        float total_width = 4 * GameRender::Constants::PROMOTION_BUTTON_SIZE
                            + 3 * GameRender::Constants::PROMOTION_BUTTON_MARGIN;
        float start_x = center.x - total_width / 2.f;
        float button_y = center.y - GameRender::Constants::PROMOTION_BUTTON_SIZE / 2.f + 20.f;

        const char* labels[] = {"Q", "R", "B", "N"};
        for (int i = 0; i < 4; i++)
        {
            float x = start_x + i * (GameRender::Constants::PROMOTION_BUTTON_SIZE + GameRender::Constants::PROMOTION_BUTTON_MARGIN);
            sf::RectangleShape button(sf::Vector2f{GameRender::Constants::PROMOTION_BUTTON_SIZE,
                                                GameRender::Constants::PROMOTION_BUTTON_SIZE});
            button.setFillColor(GameRender::Constants::BUTTON_COLOR);
            button.setPosition({x, button_y});
            window_.draw(button);

            if (font_loaded_)
            {
                sf::Text label(font_, labels[i], 36);
                label.setFillColor(sf::Color::White);
                sf::FloatRect label_bounds = label.getLocalBounds();
                label.setPosition({x + (GameRender::Constants::PROMOTION_BUTTON_SIZE - label_bounds.size.x) / 2.f,
                                button_y + (GameRender::Constants::PROMOTION_BUTTON_SIZE - label_bounds.size.y) / 2.f - 10.f});
                window_.draw(label);
            }
        }
    }


    void GameManager::RenderGameOverDialog()
    {
        sf::View board_view = board_renderer_.GetView();
        sf::Vector2f center = board_view.getCenter();

        float center_x = center.x;
        float center_y = center.y;

        window_.setView(window_.getDefaultView());

        // Draw semi-transparent overlay
        sf::RectangleShape overlay(sf::Vector2f{static_cast<float>(window_.getSize().x), static_cast<float>(window_.getSize().y)});
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window_.draw(overlay);

        window_.setView(board_view);

        // Draw dialog background
        sf::RectangleShape dialog(sf::Vector2f{GameRender::Constants::DIALOG_WIDTH, GameRender::Constants::DIALOG_HEIGHT});
        dialog.setFillColor(GameRender::Constants::DIALOG_BG_COLOR);
        dialog.setOutlineColor(GameRender::Constants::DIALOG_BORDER_COLOR);
        dialog.setOutlineThickness(2.f);
        dialog.setPosition({center_x - GameRender::Constants::DIALOG_WIDTH / 2.f, center_y - GameRender::Constants::DIALOG_HEIGHT / 2.f});
        window_.draw(dialog);

        // Get result text
        std::string result_text;
        const auto& result = game_.GetGameResult();
        switch (result.GetGameState())
        {
            case GameLogic::Enums::GameState::Checkmate:
                result_text = (result.GetWinnerColor() == GameLogic::Enums::Color::Light)
                            ? "Checkmate! White Wins!"
                            : "Checkmate! Black Wins!";
                break;
            case GameLogic::Enums::GameState::Stalemate:
                result_text = "Draw by Stalemate!";
                break;
            case GameLogic::Enums::GameState::ThreeFoldRepetition:
                result_text = "Draw by Threefold Repetition!";
                break;
            case GameLogic::Enums::GameState::FiftyMoveRule:
                result_text = "Draw by Fifty Move Rule!";
                break;
            case GameLogic::Enums::GameState::InsufficientMaterial:
                result_text = "Draw by Insufficient Material!";
                break;
            default:
                result_text = "Game Over";
                break;
        }

        if (font_loaded_)
        {
            sf::Text title(font_, result_text, 24);
            title.setFillColor(sf::Color::White);
            sf::FloatRect title_bounds = title.getLocalBounds();
            title.setPosition({center_x - title_bounds.size.x / 2.f, center_y - 50.f});
            window_.draw(title);
        }

        // Draw New Game button
        sf::FloatRect new_game_rect{{center_x - GameRender::Constants::BUTTON_WIDTH / 2.f, center_y + 20.f},
                                    {GameRender::Constants::BUTTON_WIDTH, GameRender::Constants::BUTTON_HEIGHT}};
        DrawButton(new_game_rect, "New Game", true);
    }

    void GameManager::DrawButton(const sf::FloatRect& rect, const std::string& text, bool enabled)
    {
        sf::RectangleShape button(rect.size);
        button.setPosition(rect.position);
        button.setFillColor(enabled ? GameRender::Constants::BUTTON_COLOR : GameRender::Constants::BUTTON_DISABLED_COLOR);
        window_.draw(button);

        if (font_loaded_)
        {
            sf::Text button_text(font_, text, 16);
            button_text.setFillColor(GameRender::Constants::BUTTON_TEXT_COLOR);
            sf::FloatRect text_bounds = button_text.getLocalBounds();
            button_text.setPosition({rect.position.x + (rect.size.x - text_bounds.size.x) / 2.f,
                                    rect.position.y + (rect.size.y - text_bounds.size.y) / 2.f - 5.f});
            window_.draw(button_text);
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
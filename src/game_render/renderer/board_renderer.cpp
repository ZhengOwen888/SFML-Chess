#include "game_render/renderer/board_renderer.hpp"
#include "game_render/manager/asset_manager.hpp"
#include "game_render/constants.hpp"

#include "game_logic/game.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/piece.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GameRender
{
    BoardRenderer::BoardRenderer(AssetManager* asset_manager)
        : asset_manager_(asset_manager),
        highlight_renderer_(Constants::SQUARE_SIZE, /*playing_as_black*/ false),
        playing_as_black_(false),
        square_size_(Constants::SQUARE_SIZE),
        board_size_(sf::Vector2f{Constants::INITIAL_BOARD_WIDTH, Constants::INITIAL_BOARD_HEIGHT}),
        view_(sf::Rect{sf::Vector2f{0.f, 0.f}, sf::Vector2f{Constants::INITIAL_BOARD_WIDTH, Constants::INITIAL_BOARD_HEIGHT}})
    {};

    void BoardRenderer::Render(sf::RenderWindow & window, const GameLogic::Game &game)
    {
        // UpdateView(window);
        // this->view_.setCenter(this->board_size_ / 2.f);
        // window.setView(this->view_);

        std::map<GameLogic::Position, const GameLogic::Piece*> position_and_piece = game.GetAllPositonAndPiece();

        DrawBoard(window);

        this->highlight_renderer_.Render(window);

        DrawPieces(window, position_and_piece);
    }

    void BoardRenderer::UpdateView(sf::RenderWindow &window)
    {
        sf::Vector2f window_size{window.getSize()};
        float window_width = window_size.x;
        float window_height = window_size.y;

        float scale_x = window_width / this->board_size_.x;
        float scale_y = window_height / this->board_size_.y;
        float lowest_scale = std::min(scale_x, scale_y);

        // Calculate the number of pixel dimension the new view is taking up
        int view_width_pixels = static_cast<int>(this->board_size_.x * lowest_scale);
        int view_height_pixels = static_cast<int>(this->board_size_.y * lowest_scale);

        // Calculate the top left corner position of the view so we can position it in the center
        int start_x = static_cast<int>((window_width - view_width_pixels) / 2.f);
        int start_y = static_cast<int>((window_height - view_height_pixels) / 2.f);

        // Set the viewport of the view to the center of the window.
        this->view_.setViewport(sf::FloatRect {
            // The percentage of the distance from the top and left to the view to the window size.
            sf::Vector2f
            {
                // static_cast<float>(start_x) / window_width,
                static_cast<float>(start_x) / window_width,
                static_cast<float>(start_y) / window_height
            },
            // The percentage of the views size to the window size.
            sf::Vector2f
            {
                static_cast<float>(view_width_pixels) / window_width,
                static_cast<float>(view_height_pixels) / window_height
            }
        });

        // Set the internal view size back to 800x800 world units
        this->view_.setSize(this->board_size_);
        this->view_.setCenter(this->board_size_ / 2.f);

        window.setView(this->view_);
    }

    void BoardRenderer::TogglePerspective(bool play_as_black)
    {
        this->playing_as_black_ = play_as_black;
        this->highlight_renderer_.SetPlayingAsBlack(play_as_black);
    }

    void BoardRenderer::SetPositionsToHighlight(
        const GameLogic::Position &selected_position,
        const sf::Color &selected_position_color,
        const std::map<GameLogic::Position, sf::Color> &positions_to_highlight_with_colors)
    {
        this->highlight_renderer_.SetPositionsToHighlight(selected_position, selected_position_color, positions_to_highlight_with_colors);
    }

    bool BoardRenderer::SetAndLoadPieceTheme(Enums::Theme theme)
    {
        return this->asset_manager_->SetAndLoadPieceTheme(theme);
    }

    bool BoardRenderer::SetAndLoadBoardTheme(Enums::Theme theme)
    {
        return this->asset_manager_->SetAndLoadBoardTheme(theme);
    }

    sf::Vector2f BoardRenderer::GetSquareCenter(int col, int row)
    {
        int effective_col = col;
        int effective_row = row;

        if (this->playing_as_black_ == true)
        {
            effective_col = 7 - col;
            effective_row = 7 - row;
        }

        // X depends on COL (horizontal file a through h)
        float x_pos = effective_col * this->square_size_ + this->square_size_ / 2.f;
        // Y depends on ROW (vertical rank 8 through 1)
        float y_pos = effective_row * this->square_size_ + this->square_size_ / 2.f;

        return sf::Vector2f{x_pos, y_pos};
    }

    void BoardRenderer::DrawBoard(sf::RenderWindow &window)
    {
        const sf::Texture &board_texture = this->asset_manager_->GetBoardTexture();

        sf::Vector2f board_texture_size(board_texture.getSize());
        sf::Vector2f board_scale =
        {
            this->board_size_.x / board_texture_size.x,
            this->board_size_.y / board_texture_size.y
        };

        sf::Sprite board_sprite(board_texture);
        board_sprite.setPosition(sf::Vector2f{0.f, 0.f});
        board_sprite.setScale(board_scale);

        if (this->playing_as_black_)
        {
            board_sprite.setOrigin(board_sprite.getLocalBounds().getCenter());
            board_sprite.setRotation(sf::degrees(180.f));
            board_sprite.setOrigin(board_sprite.getLocalBounds().size);
        }
        else
        {
            board_sprite.setOrigin(sf::Vector2f{0.f, 0.f});
            board_sprite.setRotation(sf::degrees(0.f));
        }

        window.draw(board_sprite);
    }

    void BoardRenderer::DrawPieces(sf::RenderWindow &window, const std::map<GameLogic::Position, const GameLogic::Piece *> pieces)
    {
        for (const auto& [position, piece] : pieces)
        {
            GameLogic::Enums::Color piece_color = piece->GetColor();
            GameLogic::Enums::PieceType piece_type = piece->GetPieceType();
            sf::Texture piece_texture = this->asset_manager_->GetPieceTexture(piece_color, piece_type);
            piece_texture.setSmooth(true);

            sf::Sprite piece_sprite(piece_texture);

            sf::Vector2f origin =
            {
                piece_texture.getSize().x / 2.f,
                piece_texture.getSize().y / 2.f
            };
            sf::Vector2f scale =
            {
                this->square_size_ / piece_texture.getSize().x,
                this->square_size_ / piece_texture.getSize().y
            };

            piece_sprite.setOrigin(origin);
            piece_sprite.setScale(scale);

            sf::Vector2f square_center_pos = GetSquareCenter(position.GetCol(), position.GetRow());
            piece_sprite.setPosition(square_center_pos);

            window.draw(piece_sprite);
        }
    }

    sf::View BoardRenderer::GetView()
    {
        return this->view_;
    }
} // namespace GameRender
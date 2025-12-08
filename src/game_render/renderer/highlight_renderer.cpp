#include "game_render/renderer/highlight_renderer.hpp"

#include "game_logic/base/position.hpp"
#include "game_logic/constants.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GameRender
{
    HighlightRenderer::HighlightRenderer(float square_size, bool playing_as_black)
        : square_size_(square_size),
        playing_as_black_(playing_as_black),
        selected_position_(GameLogic::Position{-1, -1}),
        selected_position_color_(sf::Color::Transparent)
    {};

    void HighlightRenderer::Render(sf::RenderWindow &window)
    {
        HighlightSelectedPosition(window);
        HighlightPossibleMoves(window);
    }

    void HighlightRenderer::SetPositionsToHighlight(
        const GameLogic::Position &selected_position,
        const sf::Color &selected_position_color,
        const std::map<GameLogic::Position, sf::Color> &positions_to_highlight_with_colors)
    {
        this->selected_position_ = selected_position;
        this->selected_position_color_ = selected_position_color;
        this->positions_to_highlight_with_colors_ = positions_to_highlight_with_colors;
    }

    void HighlightRenderer::SetPlayingAsBlack(bool play_as_black)
    {
        this->playing_as_black_ = play_as_black;
    }

    sf::Vector2f HighlightRenderer::GetSquareTopLeftCorner(int col, int row)
    {
        int effective_col = col;
        int effective_row = row;

        if (this->playing_as_black_ == true)
        {
            effective_col = 7 - col;
            effective_row = 7 - row;
        }

        float x_pos = effective_col * this->square_size_;
        float y_pos = effective_row * this->square_size_;

        return sf::Vector2f{x_pos, y_pos};
    }

    sf::RectangleShape HighlightRenderer::GetHighlightedSquare(const GameLogic::Position &position, const sf::Color &color)
    {
        int col = position.GetCol();
        int row = position.GetRow();
        sf::Vector2f top_left_corner_pos = GetSquareTopLeftCorner(col, row);

        sf::RectangleShape highlighted_square(sf::Vector2f{this->square_size_, this->square_size_});
        highlighted_square.setPosition(top_left_corner_pos);
        highlighted_square.setFillColor(color);

        return highlighted_square;
    }

    void HighlightRenderer::HighlightSelectedPosition(sf::RenderWindow &window)
    {
        int col = this->selected_position_.GetCol();
        int row = this->selected_position_.GetRow();

        if (IsValidPosition(col, row))
        {
            sf::RectangleShape highlighted_square = GetHighlightedSquare(this->selected_position_, this->selected_position_color_);
            window.draw(highlighted_square);
        }
    }

    void HighlightRenderer::HighlightPossibleMoves(sf::RenderWindow &window)
    {
        for (const auto& [position, color] : this->positions_to_highlight_with_colors_)
        {
            int col = position.GetCol();
            int row = position.GetRow();

            if (IsValidPosition(col, row))
            {
                sf::RectangleShape highlighted_square = GetHighlightedSquare(position, color);
                window.draw(highlighted_square);
            }
        }
    }

    bool HighlightRenderer::IsValidPosition(int col, int row)
    {
        if (col >= 0 && col < GameLogic::Constants::BOARD_SIZE && row >= 0 && row < GameLogic::Constants::BOARD_SIZE)
        {
            return true;
        }
        return false;
    }
} // namespace GameRender
#include "game_render/renderer/highlight_renderer.hpp"

#include "game_logic/base/position.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace GameRender
{
    HighlightRenderer::HighlightRenderer(float square_size, bool playing_as_black)
        : square_size_(square_size), playing_as_black_(playing_as_black) {};

    void HighlightRenderer::Render(sf::RenderWindow &window)
    {
        HighlightSelectedPosition(window);
        HighlightPossibleMoves(window);
    }

    void HighlightRenderer::SetPositionsToHighlight(
        const GameLogic::Position &selected_position, const std::vector<GameLogic::Position> &positions_to_highlight)
    {
        this->selected_position_ = selected_position;

        this->positions_to_highlight_.clear();
        this->positions_to_highlight_ = positions_to_highlight;
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
        sf::RectangleShape highlighted_square = GetHighlightedSquare(this->selected_position_, sf::Color{179, 158, 180, 128});

        window.draw(highlighted_square);
    }

    void HighlightRenderer::HighlightPossibleMoves(sf::RenderWindow &window)
    {
        for (const auto& position : positions_to_highlight_)
        {
            // sf::Color{118, 150, 86, 128}
            sf::RectangleShape highlighted_square = GetHighlightedSquare(position, sf::Color{179, 158, 180, 128});
            window.draw(highlighted_square);
        }
    }
} // namespace GameRender
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "SFML_CHESS",
        sf::Style::Default
    );

    sf::Texture board_texture;
    board_texture.loadFromFile("assets/board/board.png");

    sf::Sprite board_sprite(board_texture);

    // Center origin of board
    board_sprite.setOrigin(sf::Vector2f{board_texture.getSize().x / 2.f, board_texture.getSize().y / 2.f});

    // Place it in the center of logical 800x800 space
    board_sprite.setPosition(sf::Vector2{400.f, 400.f});


    const sf::Vector2f boardSize(800.f, 800.f);

    sf::View view(sf::Rect(sf::Vector2f{0.f, 0.f}, sf::Vector2f{boardSize.x, boardSize.y}));

    auto updateView = [&](sf::Vector2u winSize)
    {
        float w = winSize.x;
        float h = winSize.y;

        float scaleX = w / boardSize.x;
        float scaleY = h / boardSize.y;
        float lowest = std::min(scaleX, scaleY);

        sf::Vector2f newViewSize = sf::Vector2f(w, h) / lowest;

        view.setSize(newViewSize);

        // Center the view around the board
        view.setCenter(sf::Vector2{400.f, 400.f});

        window.setView(view);
    };

    updateView(window.getSize());

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
                updateView({ resized->size.x, resized->size.y });
        }

        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(board_sprite);
        window.display();
    }

    return 0;
}

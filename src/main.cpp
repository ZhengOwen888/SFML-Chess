#include "game_logic/game.hpp"
#include "game_render/constants.hpp"
#include "game_render/manager/asset_manager.hpp"
#include "game_render/renderer/board_renderer.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "SFML_CHESS",
        sf::Style::Default
    );

    GameLogic::Game game;

    GameRender::AssetManager* asset_manager = GameRender::AssetManager::GetInstance();
    GameRender::BoardRenderer board_renderer{*asset_manager};

    asset_manager->SetAndLoadTheme(GameRender::Enums::Theme::Ocean);
    board_renderer.UpdateView(window);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
                board_renderer.UpdateView(window);
        }

        board_renderer.Render(window, game);

        window.display();
    }

    return 0;
}
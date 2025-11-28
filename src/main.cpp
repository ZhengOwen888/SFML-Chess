// #include "game_logic/game.hpp"
// #include "game_render/constants.hpp"
// #include "game_render/manager/asset_manager.hpp"
// #include "game_render/renderer/board_renderer.hpp"

// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>
// #include <iostream>

#include "chess_app/game_manager.hpp"

int main()
{

    ChessApp::GameManager game_manager;
    game_manager.Run();
    // sf::RenderWindow window(
    //     sf::VideoMode({800, 800}),
    //     "SFML_CHESS",
    //     sf::Style::Default
    // );

    // GameLogic::Game game;

    // GameRender::AssetManager* asset_manager = GameRender::AssetManager::GetInstance();
    // GameRender::BoardRenderer board_renderer{*asset_manager};

    // asset_manager->SetAndLoadTheme(GameRender::Enums::Theme::Ocean);
    // board_renderer.UpdateView(window);

    // int click_counter = 0;

    // GameLogic::Position from_position;
    // GameLogic::Position to_position;

    // while (window.isOpen())
    // {
    //     // check all the window's events that were triggered since the last iteration of the loop
    //     while (const std::optional event = window.pollEvent())
    //     {
    //         // "close requested" event: we close the window
    //         if (event->is<sf::Event::Closed>())
    //         {
    //             window.close();
    //         }
    //         else if (const auto* mouse_button_event = event->getIf<sf::Event::MouseButtonPressed>())
    //         {
    //             if (mouse_button_event->button == sf::Mouse::Button::Left)
    //             {
    //                 sf::Vector2i mouse_clicked_pos = mouse_button_event->position;
    //                 sf::Vector2f world_pos = window.mapPixelToCoords(mouse_clicked_pos);

    //                 int col = static_cast<int>(world_pos.x / GameRender::Constants::SQUARE_SIZE);
    //                 int row = static_cast<int>(world_pos.y / GameRender::Constants::SQUARE_SIZE);

    //                 click_counter++;

    //                 if (row >= 0 && row < 8 && col >= 0 && col < 8)
    //                 {
    //                     GameLogic::Position selected_position{row, col};

    //                     if (click_counter == 1)
    //                     {
    //                         from_position = selected_position;
    //                         const auto legal_moves = game.GetLegalMovesAtPosition(selected_position);

    //                         std::vector<GameLogic::Position> legal_positions;
    //                         for (const auto moves : legal_moves)
    //                         {
    //                             legal_positions.push_back(moves.GetToPosition());
    //                         }

    //                         board_renderer.SetPositionsToHighlight(selected_position, legal_positions);
    //                     }
    //                     if (click_counter == 2)
    //                     {
    //                         to_position = selected_position;
    //                         const auto legal_moves = game.GetLegalMovesAtPosition(selected_position);
    //                         auto it = std::find(legal_moves.begin(), legal_moves.end(), GameLogic::Move{GameLogic::Enums::MoveType::Normal, from_position, to_position});

    //                         if (it != legal_moves.end())
    //                         {
    //                             game.ExecuteMove(*it);
    //                             click_counter = 0;
    //                         }
    //                         else
    //                         {
    //                             from_position = selected_position;
    //                             const auto legal_moves = game.GetLegalMovesAtPosition(selected_position);

    //                             std::vector<GameLogic::Position> legal_positions;
    //                             for (const auto moves : legal_moves)
    //                             {
    //                                 legal_positions.push_back(moves.GetToPosition());
    //                             }

    //                             board_renderer.SetPositionsToHighlight(selected_position, legal_positions);
    //                             click_counter = 1;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         else if (const auto* resized = event->getIf<sf::Event::Resized>())
    //         {
    //             board_renderer.UpdateView(window);
    //         }
    //     }

    //     board_renderer.Render(window, game);

    //     window.display();
    // }

    return 0;
}
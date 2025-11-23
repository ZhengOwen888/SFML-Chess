#include "game_logic/base/game.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    GameLogic::Game game;

    auto position_with_pieces = game.GetAllPositonAndPiece();

    for (const auto& [position, piece] : position_with_pieces)
    {

    }
}
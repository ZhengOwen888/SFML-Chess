#include "game_logic/base/game.hpp"
#include "game_render/constants.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    GameLogic::Game game;

    auto position_with_pieces = game.GetAllPositonAndPiece();

    std::cout << position_with_pieces.size() << "\n";

    for (const auto [position, piece] : position_with_pieces)
    {
        std::cout << "Position(" << position.GetRow() << ", " << position.GetCol() << ")";
        std::cout << "  |   ";
        std::cout << "Piece(" << GameRender::Constants::COLOR_STR.at(piece->GetColor()) << ", " << GameRender::Constants::PIECE_TYPE_STR.at(piece->GetPieceType()) << ")\n";
    }
}
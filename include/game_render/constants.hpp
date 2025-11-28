#ifndef GAMERENDER_CONSTANTS_HPP
#define GAMERENDER_CONSTANTS_HPP

#include "game_logic/enums.hpp"
#include "game_render/enums.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <string_view>
#include <utility>
#include <map>

namespace GameRender
{
    namespace Constants
    {
        using Color = GameLogic::Enums::Color;
        using PieceType = GameLogic::Enums::PieceType;
        using Theme = GameRender::Enums::Theme;

        inline constexpr std::string_view ASSET_PATH = "assets/";
        inline constexpr std::string_view PIECES_PATH = "assets/pieces/";
        inline constexpr std::string_view BOARDS_PATH = "assets/boards/";
        inline constexpr std::string_view ASSET_TYPE = ".png";

        inline const std::map<Color, std::string_view> COLOR_STR =
        {
            {Color::Dark, "dark"},
            {Color::Light, "light"},
            {Color::None, "none"}
        };

        inline const std::map<PieceType, std::string_view> PIECE_TYPE_STR =
        {
            {PieceType::Pawn, "pawn"},
            {PieceType::Knight, "knight"},
            {PieceType::Bishop, "bishop"},
            {PieceType::Rook, "rook"},
            {PieceType::Queen, "queen"},
            {PieceType::King, "king"},
            {PieceType::None, "none"}
        };

        inline const std::map<Theme, std::string_view> THEME_STR =
        {
            {Theme::Classic, "classic"},
            {Theme::Walnut, "walnut"},
            {Theme::Ocean, "ocean"}
        };

        inline const std::string GET_PIECE_FILE_PATH(Color color, PieceType piece_type, Theme theme)
        {
            std::string path;
            path += PIECES_PATH;
            path += THEME_STR.at(theme);
            path += "/";
            path += COLOR_STR.at(color);
            path += "/";
            path += COLOR_STR.at(color);
            path += "_";
            path += PIECE_TYPE_STR.at(piece_type);
            path += ASSET_TYPE;
            return path;
        }

        inline const std::string GET_BOARD_FILE_PATH(Theme theme)
        {
            std::string path;
            path += BOARDS_PATH;
            path += THEME_STR.at(theme);
            path += "/board";
            path += ASSET_TYPE;
            return path;
        }

        inline constexpr float INITIAL_WINDOW_WIDTH = 800.f;
        inline constexpr float INITIAL_WINDOW_HEIGHT = INITIAL_WINDOW_WIDTH;

        inline constexpr float INITIAL_BOARD_WIDTH = INITIAL_WINDOW_WIDTH;
        inline constexpr float INITIAL_BOARD_HEIGHT = INITIAL_WINDOW_WIDTH;
        inline constexpr float SQUARE_SIZE = INITIAL_BOARD_WIDTH / 8.f;

        inline const sf::Color MOVE_HIGHLIGHT_GREEN{118, 150, 86, 128};
        inline const sf::Color INVALID_MOVE_RED{255, 0, 0, 150};
        inline const sf::Color SUCCESS_MOVE_GOLD{218, 165, 32, 128};

    } // namespace Constants

} // namespace GameRender

#endif
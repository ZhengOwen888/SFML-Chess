#ifndef GAMERENDER_ASSET_MANAGER_HPP
#define GAMERENDER_ASSET_MANAGER_HPP

#include "game_logic/enums.hpp"
#include "game_render/enums.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <utility>

namespace GameRender
{
    class AssetManager
    {
        public:
            AssetManager();
            ~AssetManager() = default;
            // Load all assets for a theme
            bool LoadAssetsForTheme(Enums::Theme = Enums::Theme::Classic);

            // Get a specific piece texture by its color and piece type
            const sf::Texture &GetPieceTexture(
                GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const;

            // Get a specific board texture
            const sf::Texture &GetBoardTexture() const;

            // Returns true if a specifc piece has texture
            bool HasPieceTexture(
                GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const;

            // Returns true if a specific board has texture
            bool HasBoardTexture() const;

        private:
            std::map<std::pair<GameLogic::Enums::Color, GameLogic::Enums::PieceType>, sf::Texture> piece_textures_;
            sf::Texture board_texture_;
            Enums::Theme current_theme_;

            bool LoadTextureFromFile(const std::string &filepath, sf::Texture &texture_target);
    };
} // namespace GameRender

#endif
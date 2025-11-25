#include "game_render/manager/asset_manager.hpp"
#include "game_render/enums.hpp"
#include "game_render/constants.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <utility>
#include <string>
#include <iostream>

namespace GameRender
{
    AssetManager::AssetManager()
        : current_theme_(Enums::Theme::Classic) {};


    // Load all assets for each piece and the board for a specific theme
    bool AssetManager::LoadAssetsForTheme(Enums::Theme theme)
    {
        this->current_theme_ = theme;

        for (auto color : GameLogic::Constants::AllColors)
        {
            for (auto piece_type : GameLogic::Constants::AllPieceType)
            {
                std::string piece_file_path = Constants::GET_PIECE_FILE_PATH(color, piece_type, theme);
                std::pair<GameLogic::Enums::Color, GameLogic::Enums::PieceType> key = {color, piece_type};

                if (!LoadTextureFromFile(piece_file_path, this->piece_textures_[key]))
                {
                    return false;
                }
            }
        }

        std::string board_file_path = Constants::GET_BOARD_FILE_PATH(theme);

        if (!LoadTextureFromFile(board_file_path, this->board_texture_))
        {
            return false;
        }

        return true;
    }

    bool AssetManager::LoadTextureFromFile(const std::string &filepath, sf::Texture &texture_target)
    {
        if (!texture_target.loadFromFile(filepath))
        {
            std::cerr << "Error: Failed to load texture from file: " << filepath << std::endl;
            return false;
        }
        return true;
    }

    const sf::Texture &AssetManager::GetPieceTexture(
        GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const
    {
        return this->piece_textures_.at(std::make_pair(color, piece_type));
    }

    const sf::Texture &AssetManager::GetBoardTexture() const
    {
        return this->board_texture_;
    }

    bool AssetManager::HasPieceTexture(
        GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const
    {
        auto it = this->piece_textures_.find(std::make_pair(color, piece_type));

        if (it != this->piece_textures_.end())
        {
            const sf::Texture& piece_texture = it->second;

            return piece_texture.getSize().x > 0 && piece_texture.getSize().y > 0;
        }

        return false;
    }

    bool AssetManager::HasBoardTexture() const
    {
        return this->board_texture_.getSize().x > 0 && this->board_texture_.getSize().y > 0;
    }

} // namespace GameRender
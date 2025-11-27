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
#include <stdexcept>

namespace GameRender
{
    AssetManager* AssetManager::instance_ptr_ = nullptr;

    AssetManager::AssetManager()
        : current_piece_theme_(Enums::Theme::Classic), current_board_theme_(Enums::Theme::Classic) {};

    AssetManager* AssetManager::GetInstance()
    {
        if (AssetManager::instance_ptr_ == nullptr)
        {
            AssetManager::instance_ptr_ = new AssetManager();
        }
        return AssetManager::instance_ptr_;
    }

    bool AssetManager::SetAndLoadTheme(Enums::Theme theme)
    {
        this->current_piece_theme_ = theme;
        this->current_board_theme_ = theme;
        return LoadAllCurrentThemes();
    }

    bool AssetManager::SetAndLoadPieceTheme(Enums::Theme theme)
    {
        this->current_piece_theme_ = theme;

        return LoadPieceTextures();
    }

    bool AssetManager::SetAndLoadBoardTheme(Enums::Theme theme)
    {
        this->current_board_theme_ = theme;

        return LoadBoardTexture();
    }

    bool AssetManager::LoadAllCurrentThemes()
    {
        LoadPieceTextures();
        LoadBoardTexture();

        return true;
    }

    const sf::Texture & AssetManager::GetPieceTexture(
        GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const
    {
        return this->piece_textures_.at({color, piece_type});
    }

    const sf::Texture & AssetManager::GetBoardTexture() const
    {
        return this->board_texture_;
    }

    bool AssetManager::LoadAssetFromFile(const std::string &filepath, sf::Texture &target_texture)
    {
        if (!target_texture.loadFromFile(filepath))
        {
            std::cerr << "Error: Failed to load texture from file path: " << filepath << std::endl;
            return false;
        }
        return true;
    }

    bool AssetManager::LoadPieceTextures()
    {
        for (auto color : GameLogic::Constants::AllColors)
        {
            for (auto piece_type : GameLogic::Constants::AllPieceType)
            {
                std::string piece_filepath = Constants::GET_PIECE_FILE_PATH(color, piece_type, this->current_piece_theme_);
                std::pair<GameLogic::Enums::Color, GameLogic::Enums::PieceType> color_piece_type_key{color, piece_type};

                if (!LoadAssetFromFile(piece_filepath, this->piece_textures_[color_piece_type_key]))
                {
                    std::string error_msg;
                    error_msg += "Fatal Error: Failed to load piece theme for theme: ";
                    error_msg += Constants::THEME_STR.at(this->current_piece_theme_);
                    throw std::runtime_error(error_msg);
                }
            }
        }
        return true;
    }

    bool AssetManager::LoadBoardTexture()
    {
        std::string board_filepath = Constants::GET_BOARD_FILE_PATH(this->current_board_theme_);
        if (!LoadAssetFromFile(board_filepath, this->board_texture_))
        {
            std::string error_msg;
            error_msg += "Fatal Error: Failed to load board theme for theme: ";
            error_msg += Constants::THEME_STR.at(this->current_board_theme_);
            throw std::runtime_error(error_msg);
        }
        return true;
    }

} // namespace GameRender
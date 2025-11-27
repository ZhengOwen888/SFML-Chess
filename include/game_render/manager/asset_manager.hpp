#ifndef GAMERENDER_ASSET_MANAGER_HPP
#define GAMERENDER_ASSET_MANAGER_HPP

#include "game_logic/enums.hpp"
#include "game_render/enums.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <utility>
#include <string>

namespace GameRender
{
    /**************************************************************************************************
     * @class AssetManager
     * @brief A Singleton class responsible for loading, storing, and providing game assets (textures).
     *
     * Manages different themes and ensures that assets are loaded.
     *************************************************************************************************/
    class AssetManager
    {
        public:
            /*****************************************************************************************************
             * @brief Following the Singleton pattern, The single and exact same Asset Manager Object is returned.
             * @return A pointer to a static instance of Asset Manager Object.
             ****************************************************************************************************/
            static AssetManager *GetInstance();

            /*******************************************************************************************************
             * @brief Set the current theme and load the textures for both the board and the pieces with that theme.
             * @param theme The theme that is to be loaded.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ******************************************************************************************************/
            bool SetAndLoadTheme(Enums::Theme theme);

            /*********************************************************************************
             * @brief Set the current theme for pieces then load their textures.
             * @param theme The theme that is to be loaded for the pieces.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadPieceTheme(Enums::Theme theme);

            /*********************************************************************************
             * @brief Set the current theme for board then load its texture.
             * @param theme The theme that is to be loaded for the board.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************/
            bool SetAndLoadBoardTheme(Enums::Theme theme);

            /*********************************************************************************************
             * @brief Load the textures for both the board and pieces based on their currently set themes.
             * @return true if it was loaded successfully, otherwise throw std::runtime_error.
             ********************************************************************************************/
            bool LoadAllCurrentThemes();


            /***********************************************************************************************
             * @brief Retrieves a read only texture for a specific piece with color for their current theme.
             * @param color The color of the piece.
             * @param piece_type The type of the piece.
             * @return A const reference to the requested sf::Texture of the piece.
             **********************************************************************************************/
            const sf::Texture &GetPieceTexture(
                GameLogic::Enums::Color color, GameLogic::Enums::PieceType piece_type) const;

            /**********************************************************************
             * @brief Retrieves a read only texture for the current board theme.
             * @return A const reference to the requested sf::Texture of the board.
             *********************************************************************/
            const sf::Texture &GetBoardTexture() const;

        private:
            /** @brief Private constructor enforces the Singleton pattern. */
            AssetManager();

            /** @brief Default Destructor. */
            ~AssetManager() = default;

            /** @brief Disable Copy Constructor. */
            AssetManager(const AssetManager &) = delete;

            /** @brief Disable Copy Assignemnt operator. */
            AssetManager &operator=(const AssetManager &) = delete;

            /** @brief The asset manager instance */
            static AssetManager *instance_ptr_;

            /** @brief Map storing the piece textures keyed by its color and piece type. */
            std::map<std::pair<GameLogic::Enums::Color, GameLogic::Enums::PieceType>, sf::Texture> piece_textures_;

            /** @brief The texture for the board. */
            sf::Texture board_texture_;

            /** @brief The current theme of the pieces. */
            Enums::Theme current_piece_theme_;

            /** @brief The current theme if the board. */
            Enums::Theme current_board_theme_;

            // -- Helpers for Loading Assets -- //

            /************************************************************************************
             * @brief Helper function to load a single texture from a file path.
             * @param filepath the path to the asset.
             * @param texture_target A reference to the sf::Texture object to load the data into.
             * @return true if texture was loaded successfully, false otherwise (does not throw).
             ***********************************************************************************/
            bool LoadAssetFromFile(const std::string &filepath, sf::Texture &texture_target);

            /**************************************************************************
             * @brief Loads all piece textures based on the current piece theme.
             * @return true if loaded successfully, otherwise throw std::runtime_error.
             *************************************************************************/
            bool LoadPieceTextures();

            /**************************************************************************
             * @brief Load the board texture based on the current board theme.
             * @return true if loaded successfully, otherwise throw std::runtime_error.
             *************************************************************************/
            bool LoadBoardTexture();
    };
} // namespace GameRender

#endif
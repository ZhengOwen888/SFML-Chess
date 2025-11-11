#include "game.hpp"
#include "board.hpp"
#include "player.hpp"
#include "enums.hpp"

namespace GameLogic
{
    // Construct a Game object
    Game::Game()
        : board_(),
        player_light_(Enums::Color::Light),
        player_dark_(Enums::Color::Dark),
        current_player_color_(Enums::Color::Light){};

    // Get all legal moves a piece can make at the given position
    std::vector<Move> Game::GetLegalMovesAtPosition(const Position &position) const
    {
        // Get the piece at the given position
        const Piece *piece = board_.GetPieceAt(position);

        // If there is no piece at the given position or the color does not match the current players turn
        if (board_.IsPositionEmpty(position) || piece->GetColor() != current_player_color_)
        {
            return {}; // Return no moves
        }

        // Return all legal moves of the piece at the given position
        return piece->GetLegalMoves(position, board_);
    }

    // Execute the move that is given by the player
    void Game::MakeMove(const Move& move)
    {
        board_.ExecuteMove(move);

        // Switch turn to opponenet
        current_player_color_ = GetOpponentPlayerColor();
    }

    // Return the current player
    const Player& Game::GetCurrentPlayer() const
    {
        if (current_player_color_ == Enums::Color::Light)
        {
            return player_light_;
        }
        else {
            return player_dark_;
        }
    }

    // Return the current player's opponent's
    const Player& Game::GetOpponentPlayer() const
    {
        if (current_player_color_ == Enums::Color::Light)
        {
            return player_dark_;
        }
        else
        {
            return player_light_;
        }
    }

    // Return the current player's color
    Enums::Color Game::GetCurrentPlayerColor() const
    {
        return current_player_color_;
    }

    // Return the current player's opponent's color
    Enums::Color Game::GetOpponentPlayerColor() const
    {
        if (current_player_color_ == Enums::Color::Light)
        {
            return Enums::Color::Dark;
        }
        else
        {
            return Enums::Color::Light;
        }
    }

} // namespace GameLogic
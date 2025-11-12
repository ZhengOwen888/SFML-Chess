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
    std::vector<Move> Game::GetLegalMovesAtPosition(const Position &position)
    {
        // Call board object to get all legal moves at the given position
        return board_.GetLegalMovesAtPosition(position);
    }

    // Execute the move that is given by the player
    // Return True and switch player turn if it was successful
    bool Game::ExecuteMove(const Move& move)
    {
         // Call board object to execute the move
        bool execute_move_success = board_.ExecuteMove(move);

        if (execute_move_success)
        {
            // Switch to opponenet's turn
            current_player_color_ = GetOpponentPlayerColor();
        }

        return execute_move_success;
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
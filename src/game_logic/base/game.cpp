#include "game_logic/base/game.hpp"
#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"

#include "game_logic/move_handler/move_validator.hpp"
#include "game_logic/move_handler/move_executor.hpp"

#include "game_logic/enums.hpp"

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
        // Get all legal moves at the given position for the board object
        return MoveValidator::GetLegalMovesAtPosition(position, this->current_player_color_, this->board_);
    }

    // Execute the move that is given by the player
    // Return True and switch player turn if it was successful
    bool Game::ExecuteMove(const Move& move)
    {
         //  Execute the move with move executor
        bool execute_move_success = MoveExecutor::ExecuteMove(move, this->board_);

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
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

    // Get all legal move a player can make
    std::vector<Move> Game::GetAllLegalMovesForPlayer(Enums::Color player_color)
    {
        return MoveValidator::GetAllLegalMovesForPlayer(player_color, board_);
    }

    // Update the game state after each move
    void Game::UpdateGameState()
    {
        // Check if the current player has any legal moves
        if (GetAllLegalMovesForPlayer(current_player_color_).size() == 0)
        {
            // Checkmate if current player has no legal moves and their king is in check
            if (MoveValidator::IsKingInCheck(current_player_color_, board_))
            {
                result_.SetWin(GetOpponentPlayerColor());
            }
            // Stalemate if current player has no legal moves but their king is not in check
            else
            {
                result_.SetDraw(Enums::GameState::Stalemate);
            }
        }
    }

    // Check if the game is over
    bool Game::IsGameOver() const
    {
        return !result_.IsOngoing();
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
            UpdateGameState();
        }

        return execute_move_success;
    }

    // Return the current player
    const Player& Game::GetCurrentPlayer() const
    {
        return (current_player_color_ == Enums::Color::Light) ? player_light_ : player_dark_;
    }

    // Return the current player's opponent's
    const Player& Game::GetOpponentPlayer() const
    {
        return (current_player_color_ == Enums::Color::Light) ? player_dark_ : player_light_;
    }

    // Return the current player's color
    Enums::Color Game::GetCurrentPlayerColor() const
    {
        return current_player_color_;
    }

    // Return the current player's opponent's color
    Enums::Color Game::GetOpponentPlayerColor() const
    {
        return (current_player_color_ == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;
    }

} // namespace GameLogic
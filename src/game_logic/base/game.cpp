#include "game_logic/base/game.hpp"
#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/game_result.hpp"

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
        Move last_move = GetLastMove();
        // Get all legal moves at the given position for the board object
        return MoveValidator::GetLegalMovesAtPosition(position, this->current_player_color_, this->board_, last_move);
    }

    // Get all legal move a player can make
    std::vector<Move> Game::GetAllLegalMovesForPlayer(Enums::Color player_color)
    {
        const Move last_move = GetLastMove();
        return MoveValidator::GetAllLegalMovesForPlayer(player_color, this->board_, last_move);
    }

    // Update the game state after each move
    void Game::UpdateGameState()
    {
        if (fifty_move_counter_ == 100)
        {
            result_.SetDraw(Enums::GameState::FiftyMoveRule);
        }
        // Check if the current player has any legal moves
        else if (GetAllLegalMovesForPlayer(this->current_player_color_).size() == 0)
        {
            // Checkmate if current player has no legal moves and their king is in check
            if (MoveValidator::IsKingInCheck(this->current_player_color_, this->board_))
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
        return !this->result_.IsOngoing();
    }

    // Execute the move that is given by the player
    bool Game::ExecuteMove(const Move& move)
    {
        // Check if the move is legal
        bool is_legal_move = MoveValidator::IsLegalMove(move, this->current_player_color_, this->board_);
        if (is_legal_move == false)
        {
            return false;
        }

        // Execute the move with move executor
        MoveExecutor::ExecuteMove(move, this->current_player_color_, this->board_);

        // Check if move captures a piece or is a pawn move
        bool is_capture_move = MoveValidator::IsCaptureMove(move, this->board_);
        bool is_pawn_move = MoveValidator::IsPawnMove(move, this->board_);

        // Update 50 move rule counter
        if (is_capture_move || is_pawn_move)
        {
            fifty_move_counter_ = 0;
        }
        fifty_move_counter_++;

        // Switch to opponenet's turn and update move_history
        this->current_player_color_ = GetOpponentPlayerColor();
        this->move_history_.push_back(move);
        UpdateGameState();

        return true;
    }

    // Return the latest move that was made
    const Move Game::GetLastMove() const
    {
        if (this->move_history_.size() == 0)
        {
            return Move(Enums::MoveType::None, Position(-1, -1), Position(-1, -1));
        }
        else
        {
            return this->move_history_.back();
        }
    }

    // Return the current player
    const Player& Game::GetCurrentPlayer() const
    {
        return (this->current_player_color_ == Enums::Color::Light) ? this->player_light_ : this->player_dark_;
    }

    // Return the current player's opponent's
    const Player& Game::GetOpponentPlayer() const
    {
        return (this->current_player_color_ == Enums::Color::Light) ? this->player_dark_ : this->player_light_;
    }

    // Return the current player's color
    Enums::Color Game::GetCurrentPlayerColor() const
    {
        return this->current_player_color_;
    }

    // Return the current player's opponent's color
    Enums::Color Game::GetOpponentPlayerColor() const
    {
        return (this->current_player_color_ == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;
    }

} // namespace GameLogic
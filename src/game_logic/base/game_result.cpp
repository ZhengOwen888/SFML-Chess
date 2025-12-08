#include "game_logic/base/game_result.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    GameResult::GameResult()
        : player_color_(Enums::Color::None), game_state_(Enums::GameState::Ongoing) {};

    // Construct a GameResult object which contain info about the game state
    GameResult::GameResult(Enums::Color player_color, Enums::GameState game_state)
        : player_color_(player_color), game_state_(game_state) {};

    // A player won by checkmate
    void GameResult::SetWin(Enums::Color winner_color)
    {
        player_color_ = winner_color;
        game_state_ = Enums::GameState::Checkmate;
    }

    // Both player ends up with a draw
    // 1. Stalemate
    // 2. ThreeFoldRepetition
    // 3. FiftyMoveRule
    // 4. InsufficientMaterial
    void GameResult::SetDraw(Enums::GameState game_state)
    {
        player_color_ = Enums::Color::None;
        game_state_ = game_state;
    }

    // Returns true if the game is still ongoing
    bool GameResult::IsOngoing() const
    {
        return game_state_ == Enums::GameState::Ongoing;
    }

    // Returns the current game state
    Enums::GameState GameResult::GetGameState() const noexcept
    {
        return game_state_;
    }

    // Returns the winner's color
    Enums::Color GameResult::GetWinnerColor() const noexcept
    {
        return player_color_;
    }

    // Reset the game result
    void GameResult::Reset()
    {
        player_color_ = Enums::Color::None;
        game_state_ = Enums::GameState::Ongoing;
    }

} // namespace GameLogic
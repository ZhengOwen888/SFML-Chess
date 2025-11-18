#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/game_result.hpp"

#include "game_logic/enums.hpp"

#include <vector>

namespace GameLogic
{
    class Game
    {
        public:
            // Construct a Game object
            Game();
            ~Game();

            // Get legal moves a piece can make at the given position
            std::vector<Move> GetLegalMovesAtPosition(const Position &position);

            // Get all legal move a player can make
            std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color);

            // Update the game state after each move
            void UpdateGameState();

            // Check if the game is over
            bool IsGameOver() const;

            // Execute the move that is given by the player
            // Return True and switch player turn if it was successful
            bool ExecuteMove(const Move& move);

            // Return the latest move made
            const Move GetLastMove() const;

            // Return the current player
            const Player &GetCurrentPlayer() const;

            // Return the current player's opponent's
            const Player &GetOpponentPlayer() const;

            // Return the current player's color
            Enums::Color GetCurrentPlayerColor() const;

            // Return the current player's opponent's color
            Enums::Color GetOpponentPlayerColor() const;

        private:
            // For core game state
            Board board_;
            Player player_light_;
            Player player_dark_;
            Enums::Color current_player_color_;

            // Move history and tracking
            std::vector<Move> move_history_;
            int fifty_move_counter_;

            // Game outcome
            GameResult result_;
    };
}

#endif
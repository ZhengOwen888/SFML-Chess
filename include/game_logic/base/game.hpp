#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"
#include "game_logic/base/move.hpp"

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

            // Get all legal moves a piece can make at the given position
            std::vector<Move> GetLegalMovesAtPosition(const Position &position);

            // Execute the move that is given by the player
            // Return True and switch player turn if it was successful
            bool ExecuteMove(const Move& move);

            // Return the current player
            const Player &GetCurrentPlayer() const;

            // Return the current player's opponent's
            const Player &GetOpponentPlayer() const;

            // Return the current player's color
            Enums::Color GetCurrentPlayerColor() const;

            // Return the current player's opponent's color
            Enums::Color GetOpponentPlayerColor() const;

        private:
            Board board_;
            Player player_light_;
            Player player_dark_;
            Enums::Color current_player_color_;
    };
}

#endif
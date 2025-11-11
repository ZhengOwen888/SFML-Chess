#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "board.hpp"
#include "player.hpp"
#include "move.hpp"
#include "enums.hpp"

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
            std::vector<Move> GetLegalMovesAtPosition(const Position &position) const;

            // Execute the move that is given by the player
            void MakeMove(const Move& move);

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
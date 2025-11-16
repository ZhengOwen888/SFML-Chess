#ifndef GAMELOGIC_MOVE_EXECUTOR_HPP
#define GAMELOGIC_MOVE_EXECUTOR_HPP

#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"

namespace GameLogic
{
    class MoveExecutor
    {
        public:
            // Returns true if move is executed successfully, otherwise false
            static bool ExecuteMove(const Move &move, Board &board);

            // Returns true if pawn is successfully promoted and false otherwise
            static bool PromotePawn(const Move &move, Board &board);

            // The board class already has a function that takes care of a bare bone move
            // We can define other helper functions that handle other move types other than normal
        };
} // namespace GameLogic

#endif
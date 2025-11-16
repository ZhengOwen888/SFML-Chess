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
            static bool ExecuteMove(const Move &move, Enums::Color player_color, Board &board);

            // does not move pawn but only promotes it to a different piece
            static void PromotePawn(const Move &move, Enums::Color player_color, Board &board);

        private:
            // The board class already has a function that takes care of a bare bone move
            // We can define other helper functions that handle other move types other than normal
            static bool ExecuteNormalMove(const Move &move, Board &board);

            static bool ExecuteEnPassantMove(const Move &move, Board &board);
    };
} // namespace GameLogic

#endif
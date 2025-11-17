#ifndef GAMELOGIC_MOVE_EXECUTOR_HPP
#define GAMELOGIC_MOVE_EXECUTOR_HPP

#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/piece.hpp"

#include <memory>

namespace GameLogic
{
    class MoveExecutor
    {
        public:
            static bool ExecuteMove(const Move &move, Enums::Color player_color, Board &board);

        private:
            // The board class already has a function that takes care of a bare bone move
            // We can define other helper functions that handle other move types other than normal
            static bool ExecuteNormalMove(const Move &move, Board &board);

            static bool ExecuteEnPassantMove(const Move &move, Board &board);

            // Returns a promoted pawn
            static std::unique_ptr<Piece> PromotePawn(Enums::PieceType piece_type, Enums::Color player_color);

            static bool ExecutePawnPromotionMove(const Move &move, Enums::Color player_color, Board &board);

            static bool ExecuteCastleMove(const Move &move, Board &board);
    };
} // namespace GameLogic

#endif
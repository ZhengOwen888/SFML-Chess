#ifndef GAMELOGIC_MOVE_VALIDATOR_HPP
#define GAMELOGIC_MOVE_VALIDATOR_HPP

#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    class MoveValidator
    {
        public:
            // Get legal moves for a piece at a given position
            static std::vector<Move> GetLegalMovesAtPosition(
                const Position &position, Enums::Color player_color, Board &board, const Move *last_move);

            // Get all legal move a player can make
            static std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board, const Move *last_move);

            // Helpers used for finding legal moves
            // Returns true if the move is legal
            static bool IsLegalMove(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if the square is under attack
            static bool IsSquareUnderAttack(Enums::Color attacker_color, const Board &board, const Position& target_position);

            // Returns true if the player's king is in check
            static bool IsKingInCheck(Enums::Color player_color, const Board &board);


            static bool IsKingSafeAfterMove(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if castling is legal
            static bool CastleMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);

            static Position FindKingPosition(const Enums::Color player_color, const Board &board);

            // Other helpers that can be used for the 50 move rule
            // Returns true if the move captures a piece
            static bool IsCaptureMove(const Move &move, const Board &board);

            // Returns true if the move uses a pawn
            static bool IsPawnMove(const Move &move, const Board &board);
    };
} // namespace GameLogic

#endif
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
                const Position &position, Enums::Color player_color,  Board &board, const Move &last_move);

            // Get all legal move a player can make
            static std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board, const Move &last_move);

            // Helpers used for finding legal moves
            // Returns true if the move is legal
            static bool IsLegalMove(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if a specified position can be attacked by a specified player
            static bool IsSquareUnderAttack(Enums::Color attacker_color, const Board &board, const Position &position);

            // Returns true if any one of the piece can capture the opponent's players king
            static bool CanCaptureOpponentKing(Enums::Color player_color, const Board &board);

            // Returns true if the player's king is in check
            static bool IsKingInCheck(Enums::Color player_color, const Board &board);

            // Returns true if normal move is legal
            static bool NormalMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if enpassant move is legal
            static bool EnPassantMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if pawn promotion is legal
            static bool PawnPromotionMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if castling is legal
            static bool CastleMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);
    };
} // namespace GameLogic

#endif
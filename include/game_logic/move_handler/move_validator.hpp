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
            static std::vector<Move> GetLegalMovesAtPosition(const Position &position, Enums::Color player_color,  Board &board);

            // Get all legal move a player can make
            static std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board);

            // Helpers used for finding legal moves
             // Returns true if the move is legal
            static bool IsLegalMove(const Move &move, Enums::Color player_color, Board &board);

            // Returns true if any one of the piece can capture the opponent's players king
            static bool CanCaptureKing(Enums::Color player_color, const Board &board);

            // Returns true if the player's king is in check
            static bool IsKingInCheck(Enums::Color player_color, const Board &board);

            // Returns true if a normal move would result in the player's king to be in check
            static bool NormalMoveLeaveKingInCheck(const Move &move, Enums::Color player_color, Board &board);

        private:
            // Helper to add castling moves if legal
            static void AddCastlingMovesIfLegal(const Position &king_position, Enums::Color player_color, Board &board, std::vector<Move> &moves);

            // Check if a square is under attack by the opponent
            static bool IsSquareUnderAttack(const Position &square, Enums::Color by_opponent, Board &board);
    };
} // namespace GameLogic

#endif
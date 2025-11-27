#ifndef GAMELOGIC_MOVE_VALIDATOR_HPP
#define GAMELOGIC_MOVE_VALIDATOR_HPP

#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    /**********************************************************************************************
     * @class MoveValidator
     * @brief A utility class providing static methods to validate chess moves based on game rules.
     *
     * This class contains functions that determine move legality, check for attacks, verify
     * castling rules, and assess check/checkmate scenarios. It does not store game state itself.
     *********************************************************************************************/
    class MoveValidator
    {
        public:
            /*****************************************************************************************************************
             * @brief Determines all truly legal moves for a piece at a given position, considering king safety.
             *
             * This function combines a piece's potential moves with validation checks (Ensures that the king is not in check)
             *
             * @param position The starting position of the piece.
             * @param player_color The color of the player making the move.
             * @param board The current state of the board.
             * @param last_move A pointer to the last move made in the game (for special rules like en passant).
             * @return A vector of legal Move objects.
             ****************************************************************************************************************/
            static std::vector<Move> GetLegalMovesAtPosition(
                const Position &position, Enums::Color player_color, Board &board, const Move *last_move);

            /*******************************************************************************
             * @brief Gathers all legal moves for a specific player across all their pieces.
             * @param player_color The color of the player whose moves are being checked.
             * @param board The current state of the board.
             * @param last_move A pointer to the last move made in the game.
             * @return A vector containing every legal Move available to the player.
             ******************************************************************************/
            static std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board, const Move *last_move);

            /**********************************************************************************************************
             * @brief Checks if a specific Move is legal for the current player for the current board state.
             * This involves a detailed check, including simulation to ensure the move doesn't leave the king in check.
             * @param move The move to validate.
             * @param player_color The color of the player attempting the move.
             * @param board The current state of the board.
             * @return true if the move adheres to all chess rules, false otherwise.
             *********************************************************************************************************/
            static bool IsLegalMove(const Move &move, Enums::Color player_color, Board &board);

            /***************************************************************************************************
             * @brief Checks if a specific square on the board is currently under attack by an opponent's piece.
             * @param attacker_color The color of the pieces doing the attacking.
             * @param board The current state of the board.
             * @param target_position The position being checked for attacks.
             * @return true if the square is being attacked, false otherwise.
             **************************************************************************************************/
            static bool IsSquareUnderAttack(Enums::Color attacker_color, const Board &board, const Position& target_position);

            /**************************************************************************
             * @brief Checks if the specified player's King is currently in check.
             * @param player_color The color of the player whose king is being checked.
             * @param board The current state of the board.
             * @return true if the King is in check, false otherwise.
             *************************************************************************/
            static bool IsKingInCheck(Enums::Color player_color, const Board &board);

            /******************************************************************************************
             * @brief Simulates a move to determine if the player's King would be safe afterward.
             * Essential for validating potential moves that might expose the King to check (pins).
             * @param move The move to simulate.
             * @param player_color The color of the player making the move.
             * @param board The current state of the board (will be temporarily modified and restored).
             * @return true if the King is safe after the move, false otherwise.
             *****************************************************************************************/
            static bool IsKingSafeAfterMove(const Move &move, Enums::Color player_color, Board &board);

            /*******************************************************************
             * @brief Determines if a specific castling move is legal
             * @param move The proposed castling move (CastleKS or CastleQS).
             * @param player_color The color of the Player attempting to castle.
             * @param board The current state of the Board.
             * @return true if the castling Move is legal, false otherwise.
             ******************************************************************/
            static bool CastleMoveIsLegal(const Move &move, Enums::Color player_color, Board &board);

            /********************************************************************************
             * @brief Finds the current position of the specified player's King on the Board.
             * @param player_color The color of the King to find.
             * @param board The current state of the board.
             * @return The Position of the King. Throws an error if the King is not found.
             *******************************************************************************/
            static Position FindKingPosition(const Enums::Color player_color, const Board &board);


            // -- Helpers for 50 Move Rule -- //

            /**************************************************************************************
             * @brief Checks if a specific move results in a Piece capture.
             * @param move The Move being evaluated.
             * @param board The current state of the Board.
             * @return true if the destination square contains an opponent's Piece, false otherwise.
             **************************************************************************************/
            static bool IsCaptureMove(const Move &move, const Board &board);

            /**************************************************************
             * @brief Checks if the Piece initiating the Move is a Pawn.
             * @param move The Move being evaluated.
             * @param board The current state of the Board.
             * @return true if the moving piece is a Pawn, false otherwise.
             *************************************************************/
            static bool IsPawnMove(const Move &move, const Board &board);
    };
} // namespace GameLogic

#endif
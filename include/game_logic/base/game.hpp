#ifndef GAMELOGIC_GAME_HEADER
#define GAMELOGIC_GAME_HEADER

#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/move_record.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/game_result.hpp"

#include "game_logic/enums.hpp"

#include <map>
#include <vector>
#include <memory>

namespace GameLogic
{
    /*********************************************************************************
     * @class Game
     * @brief Manages the state, rules, and flow of a single chess game.
     *
     * This class ties together the board state, players, move history, and game rules
     * (like check, checkmate, draws)
     ********************************************************************************/
    class Game
    {
        public:
            /** @brief Contruct a new Game object */
            Game();

            /** @brief Default Destrcutor */
            ~Game() = default;

            /************************************************************************************************
             * @brief Calculates and returns all legal moves a specific piece can make from a given position.
             * @param position The starting position of the piece.
             * @return A vector of valid Move objects.
             ***********************************************************************************************/
            std::vector<Move> GetLegalMovesAtPosition(const Position &position);

            /******************************************************************
             * @brief Calculates and returns all legal moves a player can make.
             * @param player_color The color of the player.
             * @return A vector of valid Move objects.
             *****************************************************************/
            std::vector<Move> GetAllLegalMovesForPlayer(Enums::Color player_color);

            /*******************************************************************************************
             * @brief Provides a read only map of all pieces currently on the board and their positions.
             * @return An immutable map of Position to const Piece pointers.
             ******************************************************************************************/
            const std::map<Position, const Piece *> GetAllPositonAndPiece() const;

            /***************************************************************************
             * @brief Check if the the current game state signifies the end of the game.
             * @return true if gamestate is not Ongoing, false otherwise.
             **************************************************************************/
            bool IsGameOver() const;

            /**********************************************************************************************
             * @brief Attempts to execute a given move for the current player.
             *
             * Validates the move against game rules, updates the board state, switches the current player,
             * updates game status (check/checkmate), and stores the move in history if successful.
             *
             * @param move The move to be executed.
             * @return true if the move was valid and executed successfully, false otherwise.
             *********************************************************************************************/
            bool ExecuteMove(const Move& move);

            /** @brief Undo the last move made and restore previous board state. */
            void UnExecuteMove();

            /** @brief Redo the last move that was undoed */
            void ReExecuteMove();

            /*************************************************************************************************************
             * @brief Gets a pointer to the most recently executed move.
             * @return A const pointer to the last Move object in the undo history, or nullptr if no moves have been made.
             ************************************************************************************************************/
            const Move *GetLastMove() const;

            /************************************************************
             * @brief Get a const reference to the current active player.
             * @return A const reference to the current active player.
             ***********************************************************/
            const Player &GetCurrentPlayer() const;

            /***********************************************************************
             * @brief Get a const reference to the current active player's opponent.
             * @return A const reference to the current active player's opponent.
             **********************************************************************/
            const Player &GetOpponentPlayer() const;

        private:
            // -- Core -- //

            /** @brief The representation and logic for the 8x8 chess board. */
            Board board_;

            /** @brief Player object playing with light pieces. */
            Player player_light_;

            /** @brief Player object playing with dark pieces. */
            Player player_dark_;

            /** @brief Tracks whose turn it currently is. */
            Enums::Color current_player_color_;

            // -- History -- //

            /** @brief History of moves made, used for undo. */
            std::vector<MoveRecord> undo_history_;

            /** @brief History of moves undoed, used for redo. */
            std::vector<MoveRecord> redo_history_;

            /** @brief Tracks moves since the last capture or pawn move for the fifty-move draw rule. */
            int fifty_move_counter_;

            // -- Game Outcome -- //

            /** @brief Store the current result of the game (Ongoing, Checkmate, Stalemate... ) */
            GameResult result_;

            /** @brief Helper function to update game state after each player makes a move. */
            void UpdateGameState();

            /** @brief Helper function to switch player turn after each player makes a move. */
            void SwitchPlayerTurn();
    };
}

#endif
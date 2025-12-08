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
#include <string>

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

            /************************************************************************************
             * @brief Generate the state of the board in Forsyth–Edwards Notation (FEN) Notation.
             * @return A string in FEN notation that represent the current state of the board.
             ***********************************************************************************/
            std::string GenerateFen() const;

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

            /***********************************************************************
             * @brief Get a const reference to the game result.
             * @return A const reference to the GameResult object.
             **********************************************************************/
            const GameResult &GetGameResult() const;

            /***********************************************************************
             * @brief Check if there are moves available for undo.
             * @return true if undo is possible, false otherwise.
             **********************************************************************/
            bool CanUndo() const;

            /***********************************************************************
             * @brief Check if there are moves available for redo.
             * @return true if redo is possible, false otherwise.
             **********************************************************************/
            bool CanRedo() const;

            /** @brief Reset the game to initial state. */
            void Reset();

            void DisplayBoard() const;

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

            /** @brief Stores existing board states for three fold repetition. */
            std::map<std::string, int> board_states_;

            /** @brief Tracks half moves since the last capture or pawn move for the fifty-move draw rule. */
            int fifty_move_counter_;

            /** @brief The total number of full moves made */
            int full_move_counter_;

            /** @brief History of board positions represented as strings for threefold repetition. */
            std::vector<std::string> position_history_;

            // -- Game Outcome -- //

            /** @brief Store the current result of the game (Ongoing, Checkmate, Stalemate... ) */
            GameResult result_;

            /** @brief Pending promotion type for pawn promotion moves. */
            Enums::PieceType pending_promotion_type_ = Enums::PieceType::Queen;

            /** @brief Helper function to update game state after each player makes a move. */
            void UpdateGameState();

            /** @brief Helper function to switch player turn after each player makes a move. */
            void SwitchPlayerTurn();

            /****************************************************************************************
             * @brief Helper function to update the fifty move counter after each player makes a move
             * @param is_capture   true if the move resulted in a capture, false otherwise.
             * @param is_pawn_move true if the move was a pawn move, false otherwise.
             ***************************************************************************************/
            void UpdateFiftyMoveCounter(bool is_pawn_move, bool is_capture_move);

            /****************************************************************************************
             * @brief Check if the current position has occurred three or more times.
             * @return true if threefold repetition has occurred.
             ***************************************************************************************/
            bool IsThreefoldRepetition() const;

            /****************************************************************************************
             * @brief Check if there is insufficient material for checkmate.
             * @return true if neither side can checkmate.
             ***************************************************************************************/
            bool IsInsufficientMaterial() const;


            // --- FEN Generation Helpers ---

            /******************************************************************************************
             * @brief Generates the FEN representation of the board's piece placement (Part 1 of FEN).
             *
             * Iterates over all 8 ranks (rows) from top to bottom, using numbers for empty squares
             * and piece characters (case sensitive for color). Ranks are separated by '/'.
             * Example: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" (the starting state of the board)
             *
             * @return The FEN piece placement string.
             *****************************************************************************************/
            std::string GenerateFenPiecePlacement() const;

            /*********************************************************************************
             * @brief Generates the FEN representation of the active color (Part 2 of FEN).
             *
             * Returns 'w' if it is Light's turn to move, or 'b' if it is Dark's turn to move.
             * Example: "w"
             *
             * @return The FEN active color character as a string.
             ********************************************************************************/
            std::string GenerateFenActiveColor() const;

            /***********************************************************************************
             * @brief Generates the FEN representation of castling availability (Part 3 of FEN).
             *
             * Returns "KQkq" if all castling moves are available, or a subset based on which
             * kings/rooks have moved. Returns '-' if no castling is possible.
             * Example: "KQ" or "-"
             *
             * @return The FEN castling availability string.
             **********************************************************************************/
            std::string GenerateFenCastlingRights() const;

            /******************************************************************************************
             * @brief Generates the FEN representation of the en passant target square (Part 4 of FEN).
             *
             * Returns the algebraic notation of the square immediately behind the destination
             * of the last double pawn move. Returns '-' otherwise.
             * Example: "e3" or "-"
             *
             * @return The FEN en passant target square string.
             ******************************************************************************************/
            std::string GenerateFenEnPassantSquare() const;

            /**************************************************************************************
             * @brief Generates the FEN representation of the halfmove clock (Part 5 of FEN).
             *
             * This counter tracks the number of half-moves since the last pawn advance or capture,
             * used for the 50-move draw rule.
             * Example: "0" or "15"
             *
             * @return The FEN halfmove clock value as a string.
             *************************************************************************************/
            std::string GenerateFenHalfmoveClock() const;

            /******************************************************************************************
             * @brief Generates the FEN representation of the fullmove number (Part 6 of FEN).
             *
             * The move number starts at 1 and is incremented after every full move pair (White+Black).
             * Example: "1" or "42"
             *
             * @return The FEN fullmove number value as a string.
             *****************************************************************************************/
            std::string GenerateFenFullmoveNumber() const;
    };
}

#endif
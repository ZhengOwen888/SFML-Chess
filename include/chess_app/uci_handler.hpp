#ifndef CHESSAPP_UCI_HANDLER_HPP
#define CHESSAPP_UCI_HANDLER_HPP

#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/process/pipe.hpp>

#include <string>

namespace ChessApp
{
    namespace bp = boost::process;

    /************************************************************************
     * @class UCIHandler
     * @brief Orchestrates the communication with a chess engine (Stockfish)
     *
     * This class manages the interaction between our Chess GUI and the UCI.
     ***********************************************************************/
    class UCIHandler
    {
        public:

            /*******************************************************************************************************************
             * @brief Construct a UCIHandler object that will help with the communication between Chess GUI and the Chess Engine
             * @param engine_path The path the the executable for the chess engine
             *******************************************************************************************************************/
            UCIHandler(const std::string &engine_path);

            /** @brief Destructor for UCIHandler, wait for the child process to be over and close all pipes. */
            ~UCIHandler();

            /****************************************************************************************************************************************************************
             * @brief Get the best move that can be made for this board state.
             * @param fen The string representation of the board state, current player, castling rights, enpassant target and move counters in Forsyth–Edwards Notation (FEN)
             * @param depth The depth the engines goes to search for moves.
             * @param search_time_ms The time the engine will take to search for moves in milliseconds.
             ***************************************************************************************************************************************************************/
            std::string GetBestMove(const std::string fen, int depth = 8, int search_time_ms = 2000);

        private:
            /** @brief The child process that will run the stockfish engine program. */
            bp::child process_child_;

            /** @brief Parent writes to this stream, child reads from stdin (parent's output → child's input) */
            bp::opstream pipe_os_;

            /** @brief Parent reads from this stream, child writes to stdout (child's output → parent's input) */
            bp::ipstream pipe_is_;


            /**************************************************************************************
             * @brief Create the child process and start the interactoin with the stockfish engine.
             * @param engine_path The file path to the executable for the stockfish engine.
             *************************************************************************************/
            void CreateAndConnectUCIProcess(const std::string& engine_path);

            /******************************************************************************************************************
             * @brief Send a command to the stockfish engine.
             * @param command A const reference to a string that represent the command we want the stockfish engine to execute.
             *****************************************************************************************************************/
            void SendCommand(const std::string &command);

            /******************************************************************************
             * @brief Tell the stockfish engine to use the UCI (universal chess interface).
             * @return true if the command was successful, false otherwise.
             *****************************************************************************/
            bool UseUCI();

            /*******************************************************
             * @brief Helper to synchronize the engine with the GUI.
             * @return true if it is synchronized.
             ******************************************************/
            bool IsReady();

            /* @brief Helper to quit the stockfish engine program. */
            void Quit();

            /**********************************************************************************************
             * @brief Wait for a response after sending the command to the stockfish engine.
             * @param expected_resposnse_substring The subtring that needs to be contained in the response.
             * @return A string that represent the line that contains the subtring.
             *********************************************************************************************/
            std::string WaitForResponse(const std::string &expected_response_substring);
    };
} // namespace ChessApp

#endif
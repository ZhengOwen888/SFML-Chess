#ifndef GAMELOGIC_BOARD_HPP
#define GAMELOGIC_BOARD_HPP

#include "game_logic/base/piece.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move_record.hpp"

#include <map>
#include <vector>
#include <memory>
#include <utility>

namespace GameLogic
{
    /*********************************************************************************************
     * @class Board
     * @brief Represents a standard 8x8 chess board and manages the state of the game Pieces.
     *
     * This class handles board initialization, Piece placement, movement logic, and move_history.
     ********************************************************************************************/
    class Board
    {
        public:
            /** @brief Constructs a Board while also initializing the Pieces on the Board. */
            Board();

            /** @brief Default destructor for the Board class. */
            ~Board() = default;

            /***********************************************************************************
             * @brief Make a move on the Board.
             * @param move The move that is going to be executed.
             * @return A move record that stores the move made, Piece moved, and Piece captured.
             **********************************************************************************/
            MoveRecord MakeMove(const Move& move);

            /*****************************************************************************************
             * @brief Unmake or undo a move.
             * @param record A move record that stores the move made, Piece moved, and Piece captured.
             ****************************************************************************************/
            void UnmakeMove(MoveRecord &record);

            /**********************************************************************************************
             * @brief Removes and returns a Piece on the Board at a specified Position.
             * @param position The position to remove the Piece from the Board.
             * @return A unique_ptr to the Piece we removed from the Board or nullptr if Position is empty.
             *********************************************************************************************/
            std::unique_ptr<Piece> RemovePieceAt(const Position &position);

            /**************************************************************************
             * @brief Removes and returns a Piece on the Board at a specified Position.
             * @param piece A unique_ptr to a Piece that will be placed on the Board.
             * @param position The position to place the Piece on the Board.
             *************************************************************************/
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position);

            /**********************************************************************************************
             * @brief Returns an immutable pointer to the Piece at a given position for read-only purposes.
             * @param position The position to check for a Piece.
             * @return A const pointer to the Piece object, or nullptr if the square is empty or invalid.
             *********************************************************************************************/
            const Piece* GetPieceAt(const Position &position) const;

            /*****************************************************************************************************
             * @brief Returns a map of all Positions currently occupied by a Piece.
             * @return Am immutable map where the key is the Position and the value is a const pointer to a Piece.
             ****************************************************************************************************/
            const std::map<Position, const Piece *> GetAllPositonAndPiece() const;

            /**********************************************************************************************
             * @brief Returns a mutable pointer to the Piece at a given position for modification purposes.
             * @param position The position to check for a Piece.
             * @return a mutable pointer to the Piece object, or nullptr if the square is empty or invalid.
             **********************************************************************************************/
            Piece* GetMutablePieceAt(const Position &position);

            /**************************************************************************
             * @brief Checks if a given Position is within the bounds of the 8x8 board.
             * @param position The Position to validate.
             * @return true if the Position is on the board, false otherwise.
             *************************************************************************/
            bool IsPositionOnBoard(const Position &position) const;

            /*********************************************************
             * @brief Checks if a given Position is empty
             * @param position The Position to check.
             * @return true if the position is empty, false otherwise.
             ********************************************************/
            bool IsPositionEmpty(const Position &position) const;

            /**************************************************************
             * @brief Checks if a list of given Positions are all empty.
             * @param positions The list of Positions to check.
             * @return true if the all position are empty, false otherwise.
             *************************************************************/
            bool ArePositionsEmpty(const std::vector<Position> &positions) const;

        private:
            /** @brief The 8x8 internal representation of the chess board
             *  Each element is a unique_ptr to a Piece or nullptr. */
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            /** @brief Sets up all the pieces in their starting positions.
             *  Called by the Contructor. */
            void InitializeBoard();

            /*****************************************************************************************************
             * @brief Helper function to determine the start and end positions of the rook during a castling move.
             * @param king_from_position The king's starting position.
             * @param king_to_position The king's destination position.
             * @param move_type The specific castle type (King Side or Queen Side).
             * @return A pair of Positions (Rook From Position, Rook To Position).
             ****************************************************************************************************/
            std::pair<Position, Position> GetCastleRookPositions(
                const Position& king_from_position, const Position& king_to_position, Enums::MoveType move_type) const;


            // --- Special Move Handlers --- //

            /** @brief Handles the logic for a standard piece move or a double pawn push. */
            MoveRecord MakeNormalMove(const Move& move);

            /** @brief Handles the logic sepcific to an enpassant capture move. */
            MoveRecord MakeEnPassantMove(const Move& move);

            /** @brief Handles the logic for a pawn promotion move. */
            MoveRecord MakePawnPromotionMove(const Move &move);

            /** @brief Handles the logic for a queen or king side castling move. */
            MoveRecord MakeCastleMove(const Move &move);

            // --- Special Unmake Move Handlers --- //

            /** @brief Reverts a standard move. */
            void UnmakeNormalMove(MoveRecord &record);

            /** @brief Reverts an enpassant move. */
            void UnmakeEnPassantMove(MoveRecord &record);

            /** @brief Reverts a pawn promotino move. */
            void UnmakePawnPromotionMove(MoveRecord &record);

            /** @brief Reverts a king or queen side castling move. */
            void UnmakeCastleMove(MoveRecord &record);
    };
}

#endif
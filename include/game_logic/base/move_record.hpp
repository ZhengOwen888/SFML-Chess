#ifndef GAMELOGIC_MOVE_RECORD_HPP
#define GAMELOGIC_MOVE_RECORD_HPP

#include "game_logic/base/move.hpp"
#include "game_logic/base/piece.hpp"

#include <memory>

namespace GameLogic
{
    /*******************************************************************************************************
     * @class MoveRecord
     * @brief A data structure that records the full context of a single Move execution.
     *
     * This record is essential for implementing the `UnmakeMove` (undo) functionality in the `Board` class.
     * It stores: the Move details, a clone of the piece that moved (before it moved),
     * and a unique pointer to a piece that was captured during the move.
     ******************************************************************************************************/
    class MoveRecord
    {
        public:
            /** @brief Default Constructor. */
            MoveRecord() = default;

            /** @brief Default Destructor. */
            ~MoveRecord() = default;


            /** @brief Default Move constructor. */
            MoveRecord(MoveRecord&& other_move_record) = default;

            /** @brief Default Move Assignment. */
            MoveRecord& operator=(MoveRecord&& other_move_record) = default;


            /** @brief Disable Copy Constructor. */
            MoveRecord(MoveRecord& other_move_record) = delete;

            /** @brief Disable Copy Assignment. */
            MoveRecord operator=(MoveRecord &other_move_record) = delete;


            /******************************************************
             * @brief Read the Move that was made.
             * @return A const reference to the Move that was made.
             *****************************************************/
            const Move &ReadMoveMade() const;

            /**************************************************************
             * @brief Read the Piece that was captured.
             * @return A const pointer to a Piece object that was captured.
             *************************************************************/
            const Piece *ReadCapturedPiece() const;

            /*************************************************************
             * @brief Read the Piece that was taking action.
             * @return A const pointer to a Piece object that took action.
             ************************************************************/
            const Piece *ReadMovedPiece() const;

            /********************************************************************
             * @brief Read the fifty move counter before the move was made.
             * @return A value of the fifty move counter before the move was made
             *******************************************************************/
            int ReadPrevFiftyMoveCounter() const;

            /***************************************************************************
             * @brief Take ownership in the Piece that was captured for unmaking a Move.
             * @return A unique_ptr to the Piece that was captured.
             **************************************************************************/
            std::unique_ptr<Piece> TakeCapturedPiece();

            /******************************************************************************
             * @brief Take ownership in the Piece that was took action for unmaking a Move.
             * @return A unique_ptr to the clone of the Piece that moved.
             *****************************************************************************/
            std::unique_ptr<Piece> TakeMovedPiece();


            /**********************************************************
             * @brief Sets the details of the Move made in this record.
             * @param move The Move details.
             *********************************************************/
            void SetMoveMade(const Move &move);

            /********************************************************************
             * @brief Sets the details of the Piece captured in this record.
             * @param captured_piece A unique_ptr to the Piece that was captured.
             *******************************************************************/
            void SetCapturedPiece(std::unique_ptr<Piece> captured_piece);

            /*****************************************************************************
             * @brief Sets the details of the Piece that took action in this record.
             * @param moved_piece A unique_ptr to the clone of the Piece that took action.
             ****************************************************************************/
            void SetMovedPiece(std::unique_ptr<Piece> moved_piece);

            /*****************************************************************************
             * @brief Sets the value of the 50 move counter before this move was executed.
             * @param counter The value of the counter at the time of the move.
             ****************************************************************************/
            void SetPrevFiftyMoveCounter(int counter);

        private:
            /** @brief The Move that was made */
            Move move_made_;

            /** @brief A unique_ptr to the Piece that was captured. */
            std::unique_ptr<Piece> captured_piece_;

            /** @brief A unique_ptr to the clone of the Piece that took action. */
            std::unique_ptr<Piece> moved_piece_;

            /** @brief The value of the 50 move counter immediately prior to this move being made. */
            int prev_fifty_move_counter_;
    };
} // namespace GameLogic

#endif
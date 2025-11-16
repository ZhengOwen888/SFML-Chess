#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"

#include "game_logic/move_handler/move_executor.hpp"

namespace GameLogic
{
    // Returns true if move is executed successfully, otherwise false
    bool MoveExecutor::ExecuteMove(const Move &move, Board &board)
    {
        // Execute Move base on move type
        switch (move.GetMoveType())
        {
            case Enums::MoveType::Normal:
                return ExecuteNormalMove(move, board);

            case Enums::MoveType::EnPassant:
                return ExecuteEnPassantMove(move, board);

            // The rest of the move type can also use MovePiece funciton but might neeed some extra logic

            // Invalid move type
            default:
                return false;
        }
    }

    bool MoveExecutor::ExecuteNormalMove(const Move &move, Board &board)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        return board.MovePiece(from_position, to_position);
    }

    bool MoveExecutor::ExecuteEnPassantMove(const Move &move, Board &board)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        Position capture_pawn_position(from_position.GetRow(), to_position.GetCol());
        board.RemovePieceAt(capture_pawn_position);

        return board.MovePiece(from_position, to_position);
    }

} // namespace GameLogic

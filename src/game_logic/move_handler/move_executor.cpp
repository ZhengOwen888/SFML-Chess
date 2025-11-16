#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"

#include "game_logic/move_handler/move_executor.hpp"

namespace GameLogic
{
    // Returns true if move is executed successfully, otherwise false
    bool MoveExecutor::ExecuteMove(const Move &move, Board &board)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // Return false if the move does not stay on the board
        if (!board.IsPositionOnBoard(from_position) || !board.IsPositionOnBoard(to_position))
        {
            return false;
        }

        // Check if there is a piece on starting position
        const Piece *piece = board.GetPieceAt(from_position);
        if (piece == nullptr)
        {
            return false;
        }

        // Execute Move base on move type
        switch (move.GetMoveType())
        {
            case Enums::MoveType::Normal:
                return board.MovePiece(from_position, to_position);

            case Enums::MoveType::CastleKS:
            {
                // King side castling
                // Move king two squares towards the rook
                if (!board.MovePiece(from_position, to_position))
                {
                    return false;
                }

                // Determine rook positions based on king's final position
                int king_row = to_position.GetRow();
                Position rook_from(king_row, 7); // h-file
                Position rook_to(king_row, 5);   // f-file (next to king)

                // Move rook
                return board.MovePiece(rook_from, rook_to);
            }

            case Enums::MoveType::CastleQS:
            {
                // Queen side castling
                // Move king two squares towards the rook
                if (!board.MovePiece(from_position, to_position))
                {
                    return false;
                }

                // Determine rook positions based on king's final position
                int king_row = to_position.GetRow();
                Position rook_from(king_row, 0); // a-file
                Position rook_to(king_row, 3);   // d-file (next to king)

                // Move rook
                return board.MovePiece(rook_from, rook_to);
            }

            // The rest of the move type can also use MovePiece funciton but might neeed some extra logic

            // Invalid move type
            default:
                return false;
        }
    }
} // namespace GameLogic

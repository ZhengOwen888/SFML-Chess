#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/pieces/knight.hpp"
#include "game_logic/pieces/bishop.hpp"
#include "game_logic/pieces/rook.hpp"
#include "game_logic/pieces/queen.hpp"
#include "game_logic/move_handler/move_executor.hpp"

namespace GameLogic
{
    // Returns true if move is executed successfully, otherwise false
    bool MoveExecutor::ExecuteMove(const Move &move, Enums::Color player_color, Board &board)
    {
        // Execute Move base on move type
        switch (move.GetMoveType())
        {
            case Enums::MoveType::Normal:
                return ExecuteNormalMove(move, board);

            case Enums::MoveType::EnPassant:
                return ExecuteEnPassantMove(move, board);

            case Enums::MoveType::PawnPromotion:
                // this logic promotes the pawn before moving it to the end of the board
                return ExecutePawnPromotionMove(move, player_color, board);

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

    bool MoveExecutor::ExecuteNormalMove(const Move &move, Board &board)
    {
        // Get starting position and target position
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // Move the piece from start position to destination position
        board.MovePiece(from_position, to_position);

        return true;
    }

    bool MoveExecutor::ExecuteEnPassantMove(const Move &move, Board &board)
    {
        // Get starting position and target position
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // The position of the pawn that will be captured via EnPassant
        Position capture_pawn_position(from_position.GetRow(), to_position.GetCol());

        // Remove the enemy pawn
        board.RemovePieceAt(capture_pawn_position);

        // Place current player pawn to destination position
        board.MovePiece(from_position, to_position);

        return true;
    }

    std::unique_ptr<Piece> PromotePawn(Enums::PieceType piece_type, Enums::Color player_color)
    {
        switch (piece_type)
        {
            case Enums::PieceType::Knight:
                return std::make_unique<Knight>(player_color);

            case Enums::PieceType::Bishop:
                return std::make_unique<Bishop>(player_color);

            case Enums::PieceType::Rook:
                return std::make_unique<Rook>(player_color);

            case Enums::PieceType::Queen:
                return std::make_unique<Queen>(player_color);

            default:
                return nullptr;
            }
    }

    bool MoveExecutor::ExecutePawnPromotionMove(const Move &move, Enums::Color player_color, Board &board)
    {
        // Get starting position and target position
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // Remove the pawn from its start position
        board.RemovePieceAt(from_position);

        // Remove any piece if present at the destination position
        board.RemovePieceAt(to_position);

        // Create a promoted piece, defaults to queen
        std::unique_ptr<Piece> promoted_piece = PromotePawn(Enums::PieceType::Queen, player_color);

        // Place the promoted piece at the destination position
        board.PlacePieceAt(std::move(promoted_piece), to_position);

        return true;
    }

} // namespace GameLogic

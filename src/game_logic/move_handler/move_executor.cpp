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

            // The rest of the move type can also use MovePiece function but might neeed some extra logic

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

    bool MoveExecutor::ExecuteCastleMove(const Move &move, Board &board)
    {
        Position king_from_position = move.GetFromPosition();
        Position king_to_position = move.GetToPosition();

        Position rook_from_position = move.GetMoveType() == Enums::MoveType::CastleKS
                                        ? king_from_position + Direction::East * Constants::KING_SIDE_ROOK_OFFSET
                                        : king_from_position + Direction::West * Constants::QUEEN_SIDE_ROOK_OFFSET;

        Position rook_to_position = move.GetMoveType() == Enums::MoveType::CastleQS
                                        ? king_to_position + Direction::West
                                        : king_to_position + Direction::East;

        board.MovePiece(king_from_position, king_to_position);
        board.MovePiece(rook_from_position, rook_to_position);

        return true;
    }
} // namespace GameLogic

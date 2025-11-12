#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/piece.hpp"
#include "game_logic/base/position.hpp"

#include "game_logic/move_handler/move_validator.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{

    // Helpers used for finding legal moves
    // Returns true if the move is legal
    bool MoveValidator::IsLegalMove(const Move &move, Enums::Color player_color, Board &board)
    {
        switch (move.GetMoveType())
        {
            case Enums::MoveType::Normal:
                return NormalMoveLeaveKingInCheck(move, player_color, board);
            default:
                return false;
        }
    }

    // Returns true if any one of the piece can capture the opponent's players king
    bool MoveValidator::CanCaptureKing(Enums::Color player_color, const Board &board)
    {
        // Iterate over all the square or position in the board
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position position{row, col};
                const Piece *piece = board.GetPieceAt(position);

                // Skip if there is no piece or the piece is not the same color as the player
                if (piece == nullptr || piece->GetColor() != player_color)
                {
                    continue;
                }

                // Get all potential moves for this piece
                const std::vector<Move> potential_moves = piece->GetPotentialMoves(position, board);

                // Check if any move lands on the opponent's king
                for (const Move &potential_move : potential_moves)
                {
                    Position to_position = potential_move.GetToPosition();
                    const Piece *target_piece = board.GetPieceAt(to_position);

                    // Return true if there is a piece at the target location which is also of Type King
                    if (target_piece != nullptr
                        && target_piece->GetPieceType() == Enums::PieceType::King
                        && target_piece->GetColor() != player_color)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Returns true if the player's king is in check
    bool MoveValidator::IsKingInCheck(Enums::Color player_color, const Board &board)
    {
         // The opponent color is the opposite
        Enums::Color opponent_color = (player_color == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;

        // Check if opponent can capture the player's king
        return CanCaptureKing(opponent_color, board);
    }

    // Returns true if a normal move would result in the player's king to be in check
    bool MoveValidator::NormalMoveLeaveKingInCheck(const Move &move, Enums::Color player_color, Board &board)
    {
        // Temporarily take piece from target position
        std::unique_ptr<Piece> captured_piece = board.TakePieceAt(move.GetToPosition());
        // Temporarily make the move
        board.MovePiece(move.GetFromPosition(), move.GetToPosition());

        // Check if the move results the king being in check
        bool king_in_check = IsKingInCheck(player_color, board);

        // Undo the move
        board.MovePiece(move.GetToPosition(), move.GetFromPosition());
        // Place back the captured piece
        board.PlacePieceAt(std::move(captured_piece), move.GetToPosition());

        return king_in_check;
    }
} // namespace GameLogic

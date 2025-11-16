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
        Position from = move.GetFromPosition();
        Position to = move.GetToPosition();

        // Take out the moving piece & captured piece (might be nullptr)
        std::unique_ptr<Piece> moving_piece = board.TakePieceAt(from);
        std::unique_ptr<Piece> captured_piece = board.TakePieceAt(to);

        // If no piece to move, restore and return (should not happen in normal cases)
        if (!moving_piece)
        {
            board.PlacePieceAt(std::move(captured_piece), to);
            return true;
        }

        // Temporarily place the piece at target position (without calling MovePiece)
        // This avoids updating castling rights and has_moved_ flag
        board.PlacePieceAt(std::move(moving_piece), to);

        // Check if the move results in the king being in check
        bool king_in_check = IsKingInCheck(player_color, board);

        // Undo: move piece back to original position
        std::unique_ptr<Piece> moved_back = board.TakePieceAt(to);
        board.PlacePieceAt(std::move(moved_back), from);

        // Restore the captured piece at target position
        board.PlacePieceAt(std::move(captured_piece), to);

        return king_in_check;
    }

    // Get legal moves for a piece at a given position
    std::vector<Move> MoveValidator::GetLegalMovesAtPosition(const Position &position, Enums::Color player_color, Board &board)
    {
        std::vector<Move> legal_moves;

        // Get the piece at the position
        const Piece *piece = board.GetPieceAt(position);

        // Return empty if no piece or wrong color
        if (piece == nullptr || piece->GetColor() != player_color)
        {
            return legal_moves;
        }

        // Get all potential moves for this piece
        std::vector<Move> potential_moves = piece->GetPotentialMoves(position, board);

        // Filter moves that would leave king in check
        for (const Move &move : potential_moves)
        {
            if (!NormalMoveLeaveKingInCheck(move, player_color, board))
            {
                legal_moves.push_back(move);
            }
        }

        // Add castling moves if this is a king
        if (piece->GetPieceType() == Enums::PieceType::King)
        {
            AddCastlingMovesIfLegal(position, player_color, board, legal_moves);
        }

        return legal_moves;
    }

    // Get all legal moves for a player
    std::vector<Move> MoveValidator::GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board)
    {
        std::vector<Move> all_legal_moves;

        // Iterate over all squares
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position position{row, col};
                const Piece *piece = board.GetPieceAt(position);

                // Skip if no piece or wrong color
                if (piece == nullptr || piece->GetColor() != player_color)
                {
                    continue;
                }

                // Get legal moves for this position
                std::vector<Move> moves = GetLegalMovesAtPosition(position, player_color, board);
                all_legal_moves.insert(all_legal_moves.end(), moves.begin(), moves.end());
            }
        }

        return all_legal_moves;
    }

    // Check if a square is under attack by the opponent
    bool MoveValidator::IsSquareUnderAttack(const Position &square, Enums::Color by_opponent, Board &board)
    {
        // Iterate over all squares
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position position{row, col};
                const Piece *piece = board.GetPieceAt(position);

                // Skip if no piece or not opponent's piece
                if (piece == nullptr || piece->GetColor() != by_opponent)
                {
                    continue;
                }

                // Special handling for pawns: check diagonal attack squares directly
                // Pawn attacks are independent of whether the target square is occupied
                if (piece->GetPieceType() == Enums::PieceType::Pawn)
                {
                    // Determine pawn's attack directions based on color
                    std::vector<Direction> attack_dirs;
                    if (by_opponent == Enums::Color::Light)
                    {
                        // Light pawns attack upward diagonally (North-East, North-West)
                        attack_dirs = {Direction::NorthEast, Direction::NorthWest};
                    }
                    else
                    {
                        // Dark pawns attack downward diagonally (South-East, South-West)
                        attack_dirs = {Direction::SouthEast, Direction::SouthWest};
                    }

                    // Check if square is in pawn's attack range
                    for (const Direction &dir : attack_dirs)
                    {
                        Position attack_square = position + dir;
                        if (attack_square == square)
                        {
                            return true;
                        }
                    }
                }
                else
                {
                    // For other pieces, use GetPotentialMoves
                    std::vector<Move> potential_moves = piece->GetPotentialMoves(position, board);

                    // Check if any move targets the square
                    for (const Move &move : potential_moves)
                    {
                        if (move.GetToPosition() == square)
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    // Add castling moves if legal
    void MoveValidator::AddCastlingMovesIfLegal(const Position &king_position, Enums::Color player_color, Board &board, std::vector<Move> &moves)
    {
        // 1. King must not have moved (checked via castling rights)
        // 2. King is not in check
        // 3. Squares between king and rook are empty
        // 4. King does not pass through or land on a square under attack

        // Determine opponent color
        Enums::Color opponent_color = (player_color == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;

        // Check if king is currently in check - cannot castle if in check
        if (IsKingInCheck(player_color, board))
        {
            return;
        }

        int king_row = king_position.GetRow();
        int king_col = king_position.GetCol();

        // Verify king is on starting square (row 7 for Light, row 0 for Dark, col 4 for both)
        if (king_col != 4)
        {
            return;
        }

        if (player_color == Enums::Color::Light && king_row == 7)
        {
            // Light King Side Castling (e1 -> g1)
            if (board.CanCastleLightKingSide())
            {
                // Check squares f1 (7,5) and g1 (7,6) are empty
                Position f1(7, 5);
                Position g1(7, 6);

                if (board.IsPositionEmpty(f1) && board.IsPositionEmpty(g1))
                {
                    // Check f1 and g1 are not under attack
                    if (!IsSquareUnderAttack(f1, opponent_color, board) &&
                        !IsSquareUnderAttack(g1, opponent_color, board))
                    {
                        // Verify rook is still at h1 (7,7)
                        Position h1(7, 7);
                        const Piece *rook = board.GetPieceAt(h1);
                        if (rook != nullptr &&
                            rook->GetPieceType() == Enums::PieceType::Rook &&
                            rook->GetColor() == Enums::Color::Light &&
                            !rook->HasMoved())
                        {
                            moves.push_back(Move(Enums::MoveType::CastleKS, king_position, g1));
                        }
                    }
                }
            }

            // Light Queen Side Castling (e1 -> c1)
            if (board.CanCastleLightQueenSide())
            {
                // Check squares d1 (7,3), c1 (7,2), and b1 (7,1) are empty
                Position d1(7, 3);
                Position c1(7, 2);
                Position b1(7, 1);

                if (board.IsPositionEmpty(d1) && board.IsPositionEmpty(c1) && board.IsPositionEmpty(b1))
                {
                    // Check d1 and c1 are not under attack (b1 doesn't matter for king's path)
                    if (!IsSquareUnderAttack(d1, opponent_color, board) &&
                        !IsSquareUnderAttack(c1, opponent_color, board))
                    {
                        // Verify rook is still at a1 (7,0)
                        Position a1(7, 0);
                        const Piece *rook = board.GetPieceAt(a1);
                        if (rook != nullptr &&
                            rook->GetPieceType() == Enums::PieceType::Rook &&
                            rook->GetColor() == Enums::Color::Light &&
                            !rook->HasMoved())
                        {
                            moves.push_back(Move(Enums::MoveType::CastleQS, king_position, c1));
                        }
                    }
                }
            }
        }
        else if (player_color == Enums::Color::Dark && king_row == 0)
        {
            // Dark King Side Castling (e8 -> g8)
            if (board.CanCastleDarkKingSide())
            {
                // Check squares f8 (0,5) and g8 (0,6) are empty
                Position f8(0, 5);
                Position g8(0, 6);

                if (board.IsPositionEmpty(f8) && board.IsPositionEmpty(g8))
                {
                    // Check f8 and g8 are not under attack
                    if (!IsSquareUnderAttack(f8, opponent_color, board) &&
                        !IsSquareUnderAttack(g8, opponent_color, board))
                    {
                        // Verify rook is still at h8 (0,7)
                        Position h8(0, 7);
                        const Piece *rook = board.GetPieceAt(h8);
                        if (rook != nullptr &&
                            rook->GetPieceType() == Enums::PieceType::Rook &&
                            rook->GetColor() == Enums::Color::Dark &&
                            !rook->HasMoved())
                        {
                            moves.push_back(Move(Enums::MoveType::CastleKS, king_position, g8));
                        }
                    }
                }
            }

            // Dark Queen Side Castling (e8 -> c8)
            if (board.CanCastleDarkQueenSide())
            {
                // Check squares d8 (0,3), c8 (0,2), and b8 (0,1) are empty
                Position d8(0, 3);
                Position c8(0, 2);
                Position b8(0, 1);

                if (board.IsPositionEmpty(d8) && board.IsPositionEmpty(c8) && board.IsPositionEmpty(b8))
                {
                    // Check d8 and c8 are not under attack (b8 doesn't matter for king's path)
                    if (!IsSquareUnderAttack(d8, opponent_color, board) &&
                        !IsSquareUnderAttack(c8, opponent_color, board))
                    {
                        // Verify rook is still at a8 (0,0)
                        Position a8(0, 0);
                        const Piece *rook = board.GetPieceAt(a8);
                        if (rook != nullptr &&
                            rook->GetPieceType() == Enums::PieceType::Rook &&
                            rook->GetColor() == Enums::Color::Dark &&
                            !rook->HasMoved())
                        {
                            moves.push_back(Move(Enums::MoveType::CastleQS, king_position, c8));
                        }
                    }
                }
            }
        }
    }

} // namespace GameLogic

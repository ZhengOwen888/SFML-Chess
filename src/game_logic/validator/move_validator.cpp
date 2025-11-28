#include "game_logic/base/board.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/move_record.hpp"
#include "game_logic/base/piece.hpp"
#include "game_logic/base/position.hpp"

#include "game_logic/validator/move_validator.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{

    // Get all legal moves for a piece at a given position
    std::vector<Move> MoveValidator::GetLegalMovesAtPosition(
        const Position &position, Enums::Color player_color, Board& board, const Move *last_move)
    {
        std::vector<Move> legal_moves;

        // Get the piece at the given position
        const Piece *piece = board.GetPieceAt(position);
        if (piece == nullptr || piece->GetColor() != player_color)
        {
            return {}; // No piece at given position
        }

        // Get the potential moves for the piece at the given position
        std::vector<Move> potential_moves;

        if (piece->GetPieceType() == Enums::PieceType::Pawn)
        {
            // last move is used by pawns to detect double pawn moves and enpassant
            potential_moves = piece->GetPotentialMoves(position, board, last_move);
        }
        else
        {
            potential_moves = piece->GetPotentialMoves(position, board);
        }

        // Check if each potential move is legal
        for (const Move& move : potential_moves)
        {
            if (IsLegalMove(move, player_color, board))
            {
                legal_moves.push_back(move);
            }
        }

        return legal_moves;
    }

    // Get all the legal moves for the current player's turn
    std::vector<Move> MoveValidator::GetAllLegalMovesForPlayer(Enums::Color player_color, Board &board, const Move *last_move)
    {
        std::vector<Move> legal_moves;

        // Iterate over all rows and columns of the board
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position from_position = Position(row, col);
                const Piece *piece = board.GetPieceAt(from_position);

                // Skip empty squares and enemy pieces
                if (piece == nullptr || piece->GetColor() != player_color)
                {
                    continue;
                }

                // Get all legal moves for this piece at a specified position
                std::vector<Move> legal_moves_at_pos = GetLegalMovesAtPosition(from_position, player_color, board, last_move);

                // Append the piece's legal moves to the overall legal moves
                legal_moves.insert(legal_moves.end(), legal_moves_at_pos.begin(), legal_moves_at_pos.end());
            }
        }

        return legal_moves;
    }

    // Helpers used for finding legal moves
    // Returns true if the move is legal
    bool MoveValidator::IsLegalMove(const Move &move, Enums::Color player_color, Board &board)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // Return false if either position is not on board, or there is no piece from the starting position
        if (!board.IsPositionOnBoard(from_position) || !board.IsPositionOnBoard(to_position) || board.GetPieceAt(from_position) == nullptr)
        {
            return false;
        }

        switch (move.GetMoveType())
        {
            case Enums::MoveType::Normal:
            case Enums::MoveType::DoublePawn:
            case Enums::MoveType::EnPassant:
            case Enums::MoveType::PawnPromotion:
                return IsKingSafeAfterMove(move, player_color, board);

            case Enums::MoveType::CastleKS:
            case Enums::MoveType::CastleQS:
                return CastleMoveIsLegal(move, player_color, board);

            default:
                return false;
        }
    }

    // Returns true if a specified position can be attacked by a specified player
    bool MoveValidator::IsSquareUnderAttack(Enums::Color attacker_color, const Board &board, const Position &target_position)
    {
        // Iterate over all the squares or positions in the board
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position position{row, col};
                const Piece *piece = board.GetPieceAt(position);

                // Skip if there is no piece or the piece is not the same color as the attacker
                if (piece == nullptr || piece->GetColor() != attacker_color)
                {
                    continue;
                }

                // Get all potential moves for this piece
                const std::vector<Move> potential_moves = piece->GetPotentialMoves(position, board);

                // Check if any move land on the target position
                for (const Move &potential_move : potential_moves)
                {
                    // Returns true of the piece is able to attack the target position
                    if (potential_move.GetToPosition() == target_position)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    Position MoveValidator::FindKingPosition(const Enums::Color player_color, const Board &board)
    {
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                const Piece *piece = board.GetPieceAt(Position(row, col));

                if (piece && piece->GetPieceType() == Enums::PieceType::King && piece->GetColor() == player_color)
                {
                    return Position(row, col);
                }
            }
        }

        throw std::runtime_error("King not found on the board");
    }

    // Returns true if the player's king is in check
    bool MoveValidator::IsKingInCheck(Enums::Color player_color, const Board &board)
    {
        // Check if opponent can capture the player's king
        Enums::Color opponent_color = (player_color == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;
        Position king_position = FindKingPosition(player_color, board);

        return IsSquareUnderAttack(opponent_color, board, king_position);
    }

    bool MoveValidator::IsKingSafeAfterMove(const Move &move, Enums::Color player_color, Board &board)
    {
        MoveRecord temp_move = board.MakeMove(move);
        bool king_in_check = IsKingInCheck(player_color, board);
        board.UnmakeMove(temp_move);

        return king_in_check == false;
    }

    // 1. King must not have moved (checked via castling rights) (!!! Handled in King class)
    // 2. Squares between king and rook are empty (!!! Handled in King class)
    // 3. King is not in check
    // 4. King does not pass through or land on a square under attack
    bool MoveValidator::CastleMoveIsLegal(const Move &move, Enums::Color player_color, Board &board)
    {
        Position king_position = move.GetFromPosition();
        std::vector<Position> in_between_position;

        if (IsKingInCheck(player_color, board))
        {
            return false;
        }

        // Determine the intermediate position between the king and the rook
        if (move.GetMoveType() == Enums::MoveType::CastleKS)
        {
            // King side castling, the positions between the king and the king side rook
            in_between_position =
            {
                king_position + Direction::East * 1,
                king_position + Direction::East * 2
            };
        }
        else if (move.GetMoveType() == Enums::MoveType::CastleQS)
        {
            // Queen side castling, the positions between the king and the queen side rook
            in_between_position =
            {
                king_position + Direction::West * 1,
                king_position + Direction::West * 2,
            };
        }

        Enums::Color opponent_color = (player_color == Enums::Color::Dark) ? Enums::Color::Light : Enums::Color::Dark;

        for (const Position& to_position : in_between_position)
        {
            if (IsSquareUnderAttack(opponent_color, board, to_position))
            {
                return false;
            }
        }
        return true;
    }

    // Returns true if the move captures a piece
    bool MoveValidator::IsCaptureMove(const Move &move, const Board &board)
    {
        if (move.GetMoveType() == Enums::MoveType::EnPassant)
        {
            return true;
        }
        Position to_position = move.GetToPosition();
        return board.GetPieceAt(to_position) != nullptr;
    }

    // Returns true if the move uses a pawn
    bool MoveValidator::IsPawnMove(const Move &move, const Board &board)
    {
        Position from_position = move.GetFromPosition();
        const Piece *piece = board.GetPieceAt(from_position);

        return piece != nullptr && piece->GetPieceType() == Enums::PieceType::Pawn;
    }
} // namespace GameLogic
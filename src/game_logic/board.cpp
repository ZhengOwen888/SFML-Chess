#include "position.hpp"
#include "move.hpp"

#include "board.hpp"
#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

#include "enums.hpp"
#include "constants.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{
    // Construct the Board object, initialize the 8x8 board with nullptr
    Board::Board()
    {
        InitializeBoard(); // Initialize the Pieces objects
    }

    Board::~Board() {};

    void Board::InitializeBoard()
    {
        this->board_.resize(8);  // 8 rows
        for (auto& row : this->board_) {
            row.resize(8);  // 8 columns, each element default-initialized to nullptr
        }

        // Place Dark pieces
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Dark), Position(0, 0));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Dark), Position(0, 1));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Dark), Position(0, 2));
        PlacePieceAt(std::make_unique<Queen>(Enums::Color::Dark), Position(0, 3));
        PlacePieceAt(std::make_unique<King>(Enums::Color::Dark), Position(0, 4));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Dark), Position(0, 5));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Dark), Position(0, 6));
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Dark), Position(0, 7));

        // Place Light pieces
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Light), Position(7, 0));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Light), Position(7, 1));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Light), Position(7, 2));
        PlacePieceAt(std::make_unique<Queen>(Enums::Color::Light), Position(7, 3));
        PlacePieceAt(std::make_unique<King>(Enums::Color::Light), Position(7, 4));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Light), Position(7, 5));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Light), Position(7, 6));
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Light), Position(7, 7));

        // Place Dark and Light pawns
        for (int col = 0; col < 8; col++)
        {
            PlacePieceAt(std::make_unique<Pawn>(Enums::Color::Dark), Position(1, col));
            PlacePieceAt(std::make_unique<Pawn>(Enums::Color::Light), Position(6, col));
        }
    }

    // Returns true if move is executed successfully, otherwise false
    bool Board::ExecuteMove(const Move &move)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // Get Piece object at from_position on the board
        const Piece *piece = GetPieceAt(from_position);
        if (piece == nullptr)
        {
            return false;
        }

        // Execute Move base on move type
        switch(move.GetMoveType())
        {
            case Enums::MoveType::Normal:
                return MovePiece(from_position, to_position);
            // Invalid move type
            default:
                return false;
        }
    }

    // Make a Normal move for a Piece object from one position to another on the board
    bool Board::MovePiece(const Position &from_position, const Position &to_position)
    {
        // Take the piece from the start position
        std::unique_ptr<Piece> piece = TakePieceAt(from_position);

        // Return false if no piece was taken
        if (piece == nullptr)
        {
            return false;
        }
        // Mark the piece as having moved
        piece->SetHasMoved();

        // Remove the piece at target position
        RemovePieceAt(to_position);

        // place piece from start position to target position
        PlacePieceAt(std::move(piece), to_position);

        return true;
    }

    // Removes a Piece object from a position on the board
    void Board::RemovePieceAt(const Position &position)
    {
        this->board_[position.GetRow()][position.GetCol()].reset();
    }

    // Place a Piece object at a position on the board
    void Board::PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position)
    {
        this->board_[position.GetRow()][position.GetCol()] = std::move(piece);
    }

    // Returns a unique pointer to a Piece object after taking it from a position
    std::unique_ptr<Piece> Board::TakePieceAt(const Position &position)
    {
        return std::move(this->board_[position.GetRow()][position.GetCol()]);
    }

    // Returns true if any one of the piece can capture the opponent's players king
    bool Board::CanCaptureKing(Enums::Color player_color) const
    {
        // Iterate over all the square or position
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                // Get the piece at that specific position
                Position piece_position{row, col};
                const Piece *piece = GetPieceAt(piece_position);

                // Skip if there is no piece or the piece is not the same color as the player
                if (piece == nullptr || piece->GetColor() != player_color)
                {
                    continue;
                }

                // Get all potential moves for this piece
                const std::vector<Move> potential_moves = piece->GetPotentialMoves(piece_position, *this);

                // Check if any move lands on the opponent's king
                for (const Move &potential_move : potential_moves)
                {
                    Position to_position = potential_move.GetToPosition();
                    const Piece *target_piece = GetPieceAt(to_position);

                    // Return true if there is a piece at the target location which is also of Type King
                    if (target_piece != nullptr && target_piece->GetPieceType() == Enums::PieceType::King)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Returns true if the player's king is in check
    bool Board::IsKingInCheck(Enums::Color player_color) const
    {
        // The opponent color is the opposite
        Enums::Color opponent_color = (player_color == Enums::Color::Light) ? Enums::Color::Dark : Enums::Color::Light;

        // Check if opponent can capture the player's king
        return CanCaptureKing(opponent_color);
    }

    // Returns true if a normal move would result in the player's king to be in check
    bool Board::NormalMoveLeaveKingInCheck(const Move &move, Enums::Color player_color)
    {
        // Temporarily take piece from target position
        std::unique_ptr<Piece> captured_piece = TakePieceAt(move.GetToPosition());

        // Temporarily make the move
        MovePiece(move.GetFromPosition(), move.GetToPosition());

        // Check if the move results the king being in check
        bool king_in_check = IsKingInCheck(player_color);

        // Undo the move
        MovePiece(move.GetToPosition(), move.GetFromPosition());

        // Place back the captured piece
        PlacePieceAt(std::move(captured_piece), move.GetToPosition());

        return king_in_check;
    }

    // Returns true if the move is legal
    bool Board::IsLegalMove(const Move &move, Enums::Color player_color)
    {
        // If the move leaves the king in check then the move is not legal
        switch (move.GetMoveType())
        {
            // Check normal move
            case Enums::MoveType::Normal:
                return NormalMoveLeaveKingInCheck(move, player_color);
            // Default to return false
            default:
                return false;
        }
    }

    // Get all legal moves for a piece at a given position
    std::vector<Move> Board::GetLegalMovesAtPosition(const Position& position)
    {
        std::vector<Move> legal_moves;

        // Get the piece at the given position
        const Piece *piece = GetPieceAt(position);
        if (piece == nullptr) {
            return {}; // No piece at given position
        }

        // Get the potential moves for the piece at the given position
        std::vector<Move> potential_moves = piece->GetPotentialMoves(position, *this);

        // Check if each potential move is legal
        for (const Move& potential_move : potential_moves)
        {
            if (IsLegalMove(potential_move, piece->GetColor()))
            {
                legal_moves.push_back(potential_move);
            }
        }

        return legal_moves;
    }

    // Returns a pointer to a constant Piece object at a position on the board
    const Piece* Board::GetPieceAt(const Position& position) const
    {
        return this->board_[position.GetRow()][position.GetCol()].get();
    }

    // Returns a pointer to a Piece object at a position on the board
    Piece* Board::GetMutablePieceAt(const Position& position)
    {
        return this->board_[position.GetRow()][position.GetCol()].get();
    }


    // Returns true if the given position is on the board
    bool Board::IsPositionOnBoard(const Position& position) const
    {
        return (position.GetRow() >= 0 && position.GetRow() < Constants::BOARD_SIZE)
            && (position.GetCol() >= 0 && position.GetCol() < Constants::BOARD_SIZE);
    }

    // Returns true if the no piece exist on the given position on the board
    bool Board::IsPositionEmpty(const Position& position) const
    {
        return (IsPositionOnBoard(position) && GetPieceAt(position) == nullptr);
    }

} // namespace GameLogic
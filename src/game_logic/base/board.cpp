#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/board.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/pieces/pawn.hpp"
#include "game_logic/pieces/knight.hpp"
#include "game_logic/pieces/bishop.hpp"
#include "game_logic/pieces/rook.hpp"
#include "game_logic/pieces/queen.hpp"
#include "game_logic/pieces/king.hpp"

#include "game_logic/enums.hpp"
#include "game_logic/constants.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{
    // Construct the Board object, initialize the 8x8 board with nullptr
    Board::Board()
    {
        // Initialize castling rights to true
        can_castle_light_king_side_ = true;
        can_castle_light_queen_side_ = true;
        can_castle_dark_king_side_ = true;
        can_castle_dark_queen_side_ = true;

        InitializeBoard(); // Initialize the Pieces objects
    }

    Board::~Board() {};

    void Board::InitializeBoard()
    {
        this->board_.resize(8);  // 8 rows
        for (auto& row : this->board_) {
            row.resize(8);  // 8 columns, each element initialized to nullptr
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

    // Make a Normal move for a Piece object from one position to another on the board
    bool Board::MovePiece(const Position &from_position, const Position &to_position)
    {
        // Update castling rights BEFORE moving the piece
        UpdateCastlingRights(from_position);

        // Also check if we're capturing a rook at its starting position
        UpdateCastlingRightsOnCapture(to_position);

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

    // Castling rights getters
    bool Board::CanCastleLightKingSide() const
    {
        return can_castle_light_king_side_;
    }

    bool Board::CanCastleLightQueenSide() const
    {
        return can_castle_light_queen_side_;
    }

    bool Board::CanCastleDarkKingSide() const
    {
        return can_castle_dark_king_side_;
    }

    bool Board::CanCastleDarkQueenSide() const
    {
        return can_castle_dark_queen_side_;
    }

    // Update castling rights based on piece movement
    // Called after a piece moves from a position
    void Board::UpdateCastlingRights(const Position &from_position)
    {
        int row = from_position.GetRow();
        int col = from_position.GetCol();

        // Check if the moving piece affects castling rights
        const Piece* piece = GetPieceAt(from_position);
        if (piece == nullptr)
        {
            return;
        }

        Enums::PieceType type = piece->GetPieceType();
        Enums::Color color = piece->GetColor();

        // Light side (row 7)
        if (color == Enums::Color::Light && row == 7)
        {
            // King moved from e1 (7,4)
            if (type == Enums::PieceType::King && col == 4)
            {
                can_castle_light_king_side_ = false;
                can_castle_light_queen_side_ = false;
            }
            // Rook moved from h1 (7,7) - king side
            else if (type == Enums::PieceType::Rook && col == 7)
            {
                can_castle_light_king_side_ = false;
            }
            // Rook moved from a1 (7,0) - queen side
            else if (type == Enums::PieceType::Rook && col == 0)
            {
                can_castle_light_queen_side_ = false;
            }
        }
        // Dark side (row 0)
        else if (color == Enums::Color::Dark && row == 0)
        {
            // King moved from e8 (0,4)
            if (type == Enums::PieceType::King && col == 4)
            {
                can_castle_dark_king_side_ = false;
                can_castle_dark_queen_side_ = false;
            }
            // Rook moved from h8 (0,7) - king side
            else if (type == Enums::PieceType::Rook && col == 7)
            {
                can_castle_dark_king_side_ = false;
            }
            // Rook moved from a8 (0,0) - queen side
            else if (type == Enums::PieceType::Rook && col == 0)
            {
                can_castle_dark_queen_side_ = false;
            }
        }
    }

    // Update castling rights when a piece is captured
    // Called when a piece at the capture position is about to be removed
    void Board::UpdateCastlingRightsOnCapture(const Position &capture_position)
    {
        int row = capture_position.GetRow();
        int col = capture_position.GetCol();

        // Check if a rook at starting position is being captured
        const Piece* captured_piece = GetPieceAt(capture_position);
        if (captured_piece == nullptr || captured_piece->GetPieceType() != Enums::PieceType::Rook)
        {
            return;
        }

        Enums::Color color = captured_piece->GetColor();

        // Light rook captured at starting position (row 7)
        if (color == Enums::Color::Light && row == 7)
        {
            if (col == 7) // h1 captured
            {
                can_castle_light_king_side_ = false;
            }
            else if (col == 0) // a1 captured
            {
                can_castle_light_queen_side_ = false;
            }
        }
        // Dark rook captured at starting position (row 0)
        else if (color == Enums::Color::Dark && row == 0)
        {
            if (col == 7) // h8 captured
            {
                can_castle_dark_king_side_ = false;
            }
            else if (col == 0) // a8 captured
            {
                can_castle_dark_queen_side_ = false;
            }
        }
    }

} // namespace GameLogic
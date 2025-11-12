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

} // namespace GameLogic
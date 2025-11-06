#include "board.hpp"

#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

#include "move.hpp"
#include "position.hpp"

#include "enums.hpp"

#include <vector>
#include <memory>

namespace GameLogic
{
    // construct the Board object, initialize the 8x8 board with nullptr
    Board::Board()
        : board_(std::vector(8, std::vector<std::unique_ptr<Piece>>(8, nullptr)))
    {
        InitializeBoard(); // initialize the Pieces objects
    }

    Board::~Board() {};

    void Board::InitializeBoard()
    {
        // place Dark pieces
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Dark), Position(0, 0));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Dark), Position(0, 1));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Dark), Position(0, 2));
        PlacePieceAt(std::make_unique<Queen>(Enums::Color::Dark), Position(0, 3));
        PlacePieceAt(std::make_unique<King>(Enums::Color::Dark), Position(0, 4));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Dark), Position(0, 5));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Dark), Position(0, 6));
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Dark), Position(0, 7));

        // place Light pieces
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Light), Position(7, 0));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Light), Position(7, 1));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Light), Position(7, 2));
        PlacePieceAt(std::make_unique<Queen>(Enums::Color::Light), Position(7, 3));
        PlacePieceAt(std::make_unique<King>(Enums::Color::Light), Position(7, 4));
        PlacePieceAt(std::make_unique<Bishop>(Enums::Color::Light), Position(7, 5));
        PlacePieceAt(std::make_unique<Knight>(Enums::Color::Light), Position(7, 6));
        PlacePieceAt(std::make_unique<Rook>(Enums::Color::Light), Position(7, 7));

        // place Dark and Light pawns
        for (int col = 0; col < 8; col++)
        {
            PlacePieceAt(std::make_unique<Pawn>(Enums::Color::Dark), Position(1, col));
            PlacePieceAt(std::make_unique<Pawn>(Enums::Color::Light), Position(6, col));
        }
    }


    // returns true if move is executed successfully, otherwise false
    bool Board::ExecuteMove(const Move &move)
    {
        Position from_position = move.GetFromPosition();
        Position to_position = move.GetToPosition();

        // get Piece object at from_position on the board
        const Piece *piece = GetPieceAt(from_position);
        if (piece == nullptr)
        {
            return false;
        }

        // check if the move is legal
        std::vector<Move> legal_moves = piece->GetLegalMoves(from_position, *this);
        if (std::find(legal_moves.begin(), legal_moves.end(), move) == legal_moves.end())
        {
            return false;
        }

        // execute the move
        MovePiece(from_position, to_position);
        return true;
    }

    // move a piece from one position to another position on the board
    void Board::MovePiece(const Position &from_position, const Position &to_position)
    {
        std::unique_ptr<Piece> piece = std::move(TakePieceAt(from_position));
        RemovePieceAt(to_position);
        PlacePieceAt(std::move(piece), to_position);
    }

    // removes a Piece object from a position on the board
    void Board::RemovePieceAt(const Position &position)
    {
        board_[position.GetRow()][position.GetCol()].reset();
    }

    // place a Piece object at a position on the board
    void Board::PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position)
    {
        board_[position.GetRow()][position.GetCol()] = std::move(piece);
    }

    // returns a unique pointer to a Piece object after taking it from a position
    std::unique_ptr<Piece> Board::TakePieceAt(const Position &position)
    {
        return std::move(board_[position.GetRow()][position.GetCol()]);
    }


    // returns a pointer to a constant Piece object at a position on the board
    const Piece* Board::GetPieceAt(const Position& position) const
    {
        return board_[position.GetRow()][position.GetCol()].get();
    }

    // returns a pointer to a Piece object at a position on the board
    Piece* Board::GetMutablePieceAt(const Position& position)
    {
        return board_[position.GetRow()][position.GetCol()].get();
    }


    // returns true if the given position is on the board
    bool Board::IsPositionOnBoard(const Position& position) const
    {
        return (position.GetRow() >= 0 && position.GetRow() < 8)
            && (position.GetCol() >= 0 && position.GetCol() < 8);
    }

    // returns true if the no piece exist on the given position on the board
    bool Board::IsPositionEmpty(const Position& position) const
    {
        return (IsPositionOnBoard(position) && GetPieceAt(position) == nullptr);
    }

} // namespace GameLogic
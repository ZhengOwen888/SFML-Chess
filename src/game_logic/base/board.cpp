#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/move_record.hpp"
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
#include <string>
#include <iostream>

namespace GameLogic
{
    // Construct the Board object, initialize the 8x8 board with nullptr
    Board::Board()
    {
        InitializeBoard(); // Initialize the Pieces objects
    }

    void Board::InitializeBoard()
    {
        this->board_.resize(8);  // 8 rows
        for (auto& row : this->board_)
        {
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

    void Board::ResetBoard()
    {
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                RemovePieceAt(Position{row, col});
            }
        }

        InitializeBoard();
    }

    // Make a Normal move for a Piece object from one position to another on the board
    MoveRecord Board::MakeMove(const Move& move)
    {
        switch(move.GetMoveType())
        {
            case Enums::MoveType::Normal:
            case Enums::MoveType::DoublePawn:
                return MakeNormalMove(move);

            case Enums::MoveType::EnPassant:
                return MakeEnPassantMove(move);

            case Enums::MoveType::PawnPromotion:
                return MakePawnPromotionMove(move);

            case Enums::MoveType::CastleKS:
            case Enums::MoveType::CastleQS:
                return MakeCastleMove(move);
            default:
                throw std::runtime_error("Unknown or invalid MoveType provided to MakeMove.");
        }
    }

    void Board::UnmakeMove(MoveRecord& record)
    {
        switch(record.ReadMoveMade().GetMoveType())
        {
            case Enums::MoveType::Normal:
            case Enums::MoveType::DoublePawn:
                UnmakeNormalMove(record);
                break;

            case Enums::MoveType::EnPassant:
                UnmakeEnPassantMove(record);
                break;

            case Enums::MoveType::PawnPromotion:
                UnmakePawnPromotionMove(record);
                break;

            case Enums::MoveType::CastleKS:
            case Enums::MoveType::CastleQS:
                UnmakeCastleMove(record);
                break;

            default:
                throw std::runtime_error("Unknown or invalid MoveType found in Move Record during Unmake.");
        }
    }

    MoveRecord Board::MakeNormalMove(const Move& move)
    {
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();

        MoveRecord record;
        record.SetMoveMade(move);

        std::unique_ptr<Piece> moving_piece = RemovePieceAt(from_position);
        record.SetMovedPiece(moving_piece->ClonePiece());
        moving_piece->SetHasMoved(true);

        std::unique_ptr<Piece> captured_piece = RemovePieceAt(to_position);
        record.SetCapturedPiece(std::move(captured_piece));

        PlacePieceAt(std::move(moving_piece), to_position);

        return std::move(record);
    }

    MoveRecord Board::MakeEnPassantMove(const Move& move)
    {
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();
        const Position capture_position(from_position.GetRow(), to_position.GetCol());

        MoveRecord record;
        record.SetMoveMade(move);

        std::unique_ptr<Piece> moving_piece = RemovePieceAt(from_position);
        record.SetMovedPiece(moving_piece->ClonePiece());
        moving_piece->SetHasMoved(true);

        std::unique_ptr<Piece> captured_piece = RemovePieceAt(capture_position);
        record.SetCapturedPiece(std::move(captured_piece));

        PlacePieceAt(std::move(moving_piece), to_position);

        return std::move(record);
    }

    MoveRecord Board::MakePawnPromotionMove(const Move &move)
    {
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();
        Enums::PieceType promoted_piece_type = move.GetPromotionPieceType();

        MoveRecord record;
        record.SetMoveMade(move);

        std::unique_ptr<Piece> moving_piece = RemovePieceAt(from_position);
        record.SetMovedPiece(moving_piece->ClonePiece());

        std::unique_ptr<Piece> captured_piece = RemovePieceAt(to_position);
        record.SetCapturedPiece(std::move(captured_piece));

        std::unique_ptr<Piece> promoted_piece;

        switch (promoted_piece_type)
        {
            case (Enums::PieceType::Bishop):
                promoted_piece = std::make_unique<Bishop>(moving_piece->GetColor());
                break;
            case (Enums::PieceType::Knight):
                promoted_piece = std::make_unique<Knight>(moving_piece->GetColor());
                break;
            case (Enums::PieceType::Rook):
                promoted_piece = std::make_unique<Rook>(moving_piece->GetColor());
                break;
            case (Enums::PieceType::Queen):
                promoted_piece = std::make_unique<Queen>(moving_piece->GetColor());
                break;
            default:
                promoted_piece = std::make_unique<Queen>(moving_piece->GetColor());
                break;
        }
        promoted_piece->SetHasMoved(true);
        PlacePieceAt(std::move(promoted_piece), to_position);

        return std::move(record);
    }

    MoveRecord Board::MakeCastleMove(const Move &move)
    {
        const Position &king_from_position = move.GetFromPosition();
        const Position &king_to_position = move.GetToPosition();

        auto [rook_from_position, rook_to_position] = GetCastleRookPositions(king_from_position, king_to_position, move.GetMoveType());

        MoveRecord record;
        record.SetMoveMade(move);

        std::unique_ptr<Piece> king_piece = RemovePieceAt(king_from_position);
        record.SetMovedPiece(king_piece->ClonePiece());
        king_piece->SetHasMoved(true);
        PlacePieceAt(std::move(king_piece), king_to_position);

        std::unique_ptr<Piece> rook_piece = RemovePieceAt(rook_from_position);
        rook_piece->SetHasMoved(true);
        PlacePieceAt(std::move(rook_piece), rook_to_position);

        record.SetCapturedPiece(nullptr);

        return std::move(record);
    }

    void Board::UnmakeNormalMove(MoveRecord &record)
    {
        const Move& move = record.ReadMoveMade();
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();

        std::unique_ptr<Piece> moved_piece = record.TakeMovedPiece();
        std::unique_ptr<Piece> captured_piece = record.TakeCapturedPiece();

        PlacePieceAt(std::move(captured_piece), to_position);
        PlacePieceAt(std::move(moved_piece), from_position);
    }

    void Board::UnmakeEnPassantMove(MoveRecord &record)
    {
        const Move& move = record.ReadMoveMade();
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();
        const Position capture_position(from_position.GetRow(), to_position.GetCol());

        std::unique_ptr<Piece> moved_piece = record.TakeMovedPiece();
        std::unique_ptr<Piece> captured_piece = record.TakeCapturedPiece();

        // Remove the pawn that did the enpassant action.
        RemovePieceAt(to_position);

        PlacePieceAt(std::move(captured_piece), capture_position);
        PlacePieceAt(std::move(moved_piece), from_position);
    }

    void Board::UnmakePawnPromotionMove(MoveRecord &record)
    {
        const Move& move = record.ReadMoveMade();
        const Position &from_position = move.GetFromPosition();
        const Position &to_position = move.GetToPosition();

        std::unique_ptr<Piece> moved_piece = record.TakeMovedPiece();
        std::unique_ptr<Piece> captured_piece = record.TakeCapturedPiece();

        PlacePieceAt(std::move(captured_piece), to_position);
        PlacePieceAt(std::move(moved_piece), from_position);
    }

    void Board::UnmakeCastleMove(MoveRecord &record)
    {
        const Move& move = record.ReadMoveMade();
        const Position& king_from_position = move.GetFromPosition();
        const Position& king_to_position = move.GetToPosition();

        auto [rook_from_position, rook_to_position] = GetCastleRookPositions(king_from_position, king_to_position, move.GetMoveType());

        std::unique_ptr<Piece> king_piece = record.TakeMovedPiece();
        king_piece->SetHasMoved(false);
        std::unique_ptr<Piece> rook_piece = RemovePieceAt(rook_to_position);
        if (rook_piece)
        {
            rook_piece->SetHasMoved(false);
        }

        PlacePieceAt(std::move(king_piece), king_from_position);
        PlacePieceAt(std::move(rook_piece), rook_from_position);
    }

    std::pair<Position, Position> Board::GetCastleRookPositions(
        const Position& king_from_position, const Position& king_to_position, Enums::MoveType move_type) const
    {
        // The position of the rook before castling
        const Position rook_from_position = move_type == Enums::MoveType::CastleKS
                                        ? king_from_position + Direction::East * Constants::KING_SIDE_ROOK_OFFSET
                                        :
                king_from_position + Direction::West *Constants::QUEEN_SIDE_ROOK_OFFSET;

                // The position of the rook after castling
                const Position rook_to_position = move_type == Enums::MoveType::CastleKS
                                                      ? king_to_position + Direction::West
                                                      : king_to_position + Direction::East;

                return {rook_from_position, rook_to_position};
    }

    // Removes a Piece object from a position on the board
    std::unique_ptr<Piece> Board::RemovePieceAt(const Position &position)
    {
        if (IsPositionOnBoard(position))
        {
            return std::move(this->board_[position.GetRow()][position.GetCol()]);
        }
        else
        {
            return nullptr;
        }
    }

    // Place a Piece object at a position on the board
    void Board::PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position)
    {
        if (IsPositionOnBoard(position))
        {
            this->board_[position.GetRow()][position.GetCol()] = std::move(piece);
        }
    }

    // Returns a pointer to a constant Piece object at a position on the board
    const Piece* Board::GetPieceAt(const Position& position) const
    {
        if (IsPositionOnBoard(position))
        {
            return this->board_[position.GetRow()][position.GetCol()].get();
        }
        else
        {
            return nullptr;
        }
    }

    // Returns a immutable map of key: position to value: pieces
    const std::map<Position, const Piece *> Board::GetAllPositonAndPiece() const
    {
        std::map<Position, const Piece *> position_with_piece;

        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                const Piece *piece = GetPieceAt(Position(row, col));
                if (piece != nullptr)
                {
                    position_with_piece[Position(row, col)] = piece;
                }
            }
        }
        return position_with_piece;
    }

    // Returns a pointer to a Piece object at a position on the board
    Piece* Board::GetMutablePieceAt(const Position& position)
    {
        if (IsPositionOnBoard(position))
        {
            return this->board_[position.GetRow()][position.GetCol()].get();
        }
        else
        {
            return nullptr;
        }
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

    // Returns true if a list of specified positions are empty
    bool Board::ArePositionsEmpty(const std::vector<Position> &positions) const
    {
        for (const Position& position : positions)
        {
            if (IsPositionEmpty(position) == false)
            {
                return false;
            }
        }
        return true;
    }

    void Board::DisplayBoard() const
    {
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            std::cout << "[";
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                const Piece *piece = GetPieceAt(Position{row, col});
                char piece_repr = '.';

                if (piece != nullptr)
                {
                    piece_repr = Constants::GET_PIECE_REPR(piece->GetColor(), piece->GetPieceType());
                }

                std::cout << piece_repr << " ";
            }
            std::cout << "]\n";
        }
    }
} // namespace GameLogic
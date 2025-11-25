#include "game_logic/base/move_record.hpp"
#include "game_logic/base/move.hpp"

#include <memory>

namespace GameLogic
{
    const Move& MoveRecord::ReadMoveMade() const
    {
        return this->move_made_;
    }

    const Piece* MoveRecord::ReadCapturedPiece() const
    {
        return this->captured_piece_.get();
    }

    const Piece* MoveRecord::ReadMovedPiece() const
    {
        return this->moved_piece_.get();
    }

    std::unique_ptr<Piece> MoveRecord::TakeCapturedPiece()
    {
        return std::move(this->captured_piece_);
    }

    std::unique_ptr<Piece> MoveRecord::TakeMovedPiece()
    {
        return std::move(this->moved_piece_);
    }

    void MoveRecord::SetMoveMade(const Move& move)
    {
        this->move_made_ = move;
    }

    void MoveRecord::SetCapturedPiece(std::unique_ptr<Piece> captured_piece)
    {
        this->captured_piece_ = std::move(captured_piece);
    }

    void MoveRecord::SetMovedPiece(std::unique_ptr<Piece> moved_piece)
    {
        this->moved_piece_ = std::move(moved_piece);
    }
} // namespace GameLogic
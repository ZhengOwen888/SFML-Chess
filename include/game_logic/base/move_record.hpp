#ifndef GAMELOGIC_MOVE_RECORD_HPP
#define GAMELOGIC_MOVE_RECORD_HPP

#include "game_logic/base/move.hpp"
#include "game_logic/base/piece.hpp"

#include <memory>

namespace GameLogic
{
    class MoveRecord
    {
        public:
            MoveRecord() = default;
            ~MoveRecord() = default;

            MoveRecord(MoveRecord&& other) = default;
            MoveRecord& operator=(MoveRecord&& other) = default;

            const Move &ReadMoveMade() const;
            const Piece *ReadCapturedPiece() const;
            const Piece *ReadMovedPiece() const;

            std::unique_ptr<Piece> TakeCapturedPiece();
            std::unique_ptr<Piece> TakeMovedPiece();

            void SetMoveMade(const Move &move);
            void SetCapturedPiece(std::unique_ptr<Piece> captured_piece);
            void SetMovedPiece(std::unique_ptr<Piece> moved_piece);

        private:
            Move move_made_;
            std::unique_ptr<Piece> captured_piece_;
            std::unique_ptr<Piece> moved_piece_;
    };
} // namespace GameLogic

#endif
#ifndef GAMELOGIC_BOARD_HPP
#define GAMELOGIC_BOARD_HPP

#include "game_logic/base/piece.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move_record.hpp"

#include <map>
#include <vector>
#include <memory>
#include <utility>

namespace GameLogic
{
    class Board
    {
        public:
            // Construct a Board object
            Board();
            ~Board() = default;

            // Helpers used to execute moves
            // Make a Normal move for a Piece object from one position to another on the board
            MoveRecord MakeMove(const Move& move);

            void UnmakeMove(MoveRecord &record);

            // Remove a Piece object at a position on the board
            std::unique_ptr<Piece> RemovePieceAt(const Position &position);

            // Place a Piece object at a position on the board
            void PlacePieceAt(std::unique_ptr<Piece> piece, const Position &position);

            // Returns an immutable piece at a given position otherwise nullptr (for read purpose only)
            const Piece* GetPieceAt(const Position &position) const;

            // Returns a immutable map of key: position to value: pieces
            const std::map<Position, const Piece *> GetAllPositonAndPiece() const;

            // Returns a mutable piece at a given position otherwise nullptr
            Piece* GetMutablePieceAt(const Position &position);

            // Returns true if position is inside board and false otherwise
            bool IsPositionOnBoard(const Position &position) const;

            // Returns true if positions has no piece on it and false otherwise
            bool IsPositionEmpty(const Position &position) const;

            // Returns true if a list of specified positions are empty
            bool ArePositionsEmpty(const std::vector<Position> &positions) const;

        private:
            // 8 by 8 vector that keeps track of what piece is on what square and if a square is empty
            std::vector<std::vector<std::unique_ptr<Piece>>> board_;

            // Set up all pieces in starting positions
            void InitializeBoard();

            MoveRecord CreateMoveRecord(const Move &move);

            std::pair<Position, Position> GetCastleRookPositions(
                const Position& king_from_position, const Position& king_to_position, Enums::MoveType move_type) const;

            MoveRecord MakeNormalMove(const Move& move);
            MoveRecord MakeEnPassantMove(const Move& move);
            MoveRecord MakePawnPromotionMove(const Move &move);
            MoveRecord MakeCastleMove(const Move &move);

            void UnmakeNormalMove(MoveRecord &record);
            void UnmakeEnPassantMove(MoveRecord &record);
            void UnmakePawnPromotionMove(MoveRecord &record);
            void UnmakeCastleMove(MoveRecord &record);
    };
}

#endif
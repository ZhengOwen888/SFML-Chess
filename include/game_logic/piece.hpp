#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"
#include "constants.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    // forward direction to avoid circular imports
    class Board;

    class Piece
    {
        public:
            // construct a Piece object with piece type and color
            Piece(Enums::PieceType piece_type, Enums::Color color);
            virtual ~Piece();

            // clone a new Piece object with the same properties
            virtual std::unique_ptr<Piece> ClonePiece() const = 0;

            // get all legal moves
            virtual std::vector<Move> GetLegalMoves(
                const Position& from_position, const Board &board) const = 0;

            // get all positions a piece can move to from its current position (in EXACTLY ONE Direction)
            std::vector<Position> GetPositionsInDir(
                const Position& from_position, const Board &board, const Direction& direction) const;

            // get all positions a piece can move to from its current position (in a SET of MANY Directions)
            std::vector<Position> GetPositionsInDirs(
                const Position& from_position, const Board &board, const std::vector<Direction>& directions) const;

            // setters
            void SetHasMoved();
            void SetHasPromoted();

            // getters
            Enums::PieceType GetPieceType() const;
            Enums::Color GetColor() const;
            bool HasMoved() const;
            bool HasPromoted() const;

        private:
            Enums::PieceType piece_type_;
            Enums::Color color_;
            bool has_moved_;    // false initially
            bool has_promoted_; // false initially
    };
} // namespace GameLogic

// === Inline implementations to keep .cpp untouched for now ===
namespace GameLogic
{
    // Constructors
    inline Piece::Piece(Enums::PieceType piece_type, Enums::Color color)
        : piece_type_(piece_type), color_(color), has_moved(false), has_promoted(false) {}

    inline Piece::Piece(Enums::PieceType piece_type, Enums::Color color, bool has_moved_, bool has_promoted_)
        : piece_type_(piece_type), color_(color), has_moved(has_moved_), has_promoted(has_promoted_) {}

    // Directional helpers (ignoring occupancy for now; just board bounds)
    inline std::vector<Position> Piece::getPositionsInDir(
        const Position& from_position, Board& /*board*/, const Direction& direction)
    {
        std::vector<Position> result;

        Position cur = from_position + direction;
        while (cur.getRow() >= 0 && cur.getRow() < Constants::BOARD_SIZE &&
               cur.getCol() >= 0 && cur.getCol() < Constants::BOARD_SIZE)
        {
            result.push_back(cur);
            cur = cur + direction;
        }
        return result;
    }

    inline std::vector<Position> Piece::getPositionsInDirs(
        const Position& from_position, Board& board, const std::vector<Direction>& directions)
    {
        std::vector<Position> result;
        for (const auto& dir : directions)
        {
            auto ray = getPositionsInDir(from_position, board, dir);
            result.insert(result.end(), ray.begin(), ray.end());
        }
        return result;
    }

    // Setters
    inline void Piece::setHasMoved() { has_moved = true; }
    inline void Piece::setHasPromoted() { has_promoted = true; }

    // Getters
    inline Enums::PieceType Piece::getPieceType() const { return piece_type_; }
    inline Enums::Color Piece::getColor() const { return color_; }
    inline bool Piece::hasMoved() const { return has_moved; }
    inline bool Piece::hasPromoted() const { return has_promoted; }
}

#endif
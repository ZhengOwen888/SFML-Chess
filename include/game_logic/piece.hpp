#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include <memory>
#include <vector>
#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"
#include "constants.hpp"

namespace GameLogic
{
    class Board; // forward direction to avoid circular imports

    class Piece
    {
        public:
            // Construct a piece with their color and or has_moved, has_promoted
            Piece(Enums::PieceType piece_type, Enums::Color color);
            Piece(Enums::PieceType piece_type, Enums::Color color, bool has_moved, bool has_promoted);
            virtual ~Piece() = default;

            // Clone creates a new piece object with the same property and values
            virtual std::unique_ptr<Piece> clonePiece() const = 0;

            // get all legal moves
            virtual std::vector<Move> getLegalMoves(
                const Position& from_position, Board &board) const = 0;

            // helper for getPositionsInDirs: it gets all the positions in one certain directioin if it is legal
            std::vector<Position> getPositionsInDir(
                const Position& from_position, Board &board, const Direction& direction);

            // helper for getLegalMoves: it gets all the positions in many directions if it is legal
            std::vector<Position> getPositionsInDirs(
                const Position& from_position, Board &board, const std::vector<Direction>& directions);

            // Setters
            void setHasMoved();
            void setHasPromoted();

            // Getters
            Enums::PieceType getPieceType() const;
            Enums::Color getColor() const;
            bool hasMoved() const;
            bool hasPromoted() const;

        private:
            Enums::PieceType piece_type_;
            Enums::Color color_;
            bool has_moved;    // false initially
            bool has_promoted; // false initially
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
#include "piece.hpp"

#include <memory>
#include <vector>
#include "board.hpp"
#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"


namespace GameLogic
{
    Piece::Piece(Enums::PieceType piece_type, Enums::Color color)
        : piece_type_(piece_type), color_(color) {};

    Piece::~Piece() {};



    std::vector<Position> Piece::getPositionsInDir(
        const Position& from_position, const Board& board, const Direction& direction) const
    {
        std::vector<Position> positions;

        for (Position pos = from_position; board.isPositionOnBoard(pos); pos = pos + direction)
        {
            if (board.isPositionEmpty(pos))
            {
                positions.push_back(pos);
                continue;
            }

            Piece* piece = board[pos].get();

            if (piece->getColor() != color_)
            {
                positions.push_back(pos);
            }
            break;
        }

        return positions;
    }

    std::vector<Position> Piece::getPositionsInDirs(
        const Position& from_position, const Board &board, const std::vector<Direction>& directions) const
    {
        std::vector<Position> positions;

        for (const Direction& dir : directions)
        {
            std::vector<Position> temp = getPositionsInDir(from_position, board, dir);
            positions.insert(positions.end(), temp.begin(), temp.end());
        }

        return positions;
    }



    // Setters
    void Piece::setHasMoved()
    {
        has_moved_ = true;
    }

    void Piece::setHasPromoted()
    {
        has_promoted_ = true;
    }



    // Getters
    Enums::PieceType Piece::getPieceType() const
    {
        return piece_type_;
    }

    Enums::Color Piece::getColor() const
    {
        return color_;
    }

    bool Piece::hasMoved() const
    {
        return has_moved_;
    }

    bool Piece::hasPromoted() const
    {
        return has_promoted_;
    }

} // namespace GameLogic
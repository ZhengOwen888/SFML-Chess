#include "board.hpp"
#include "piece.hpp"
#include "move.hpp"
#include "position.hpp"
#include "direction.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    // contruct a piece object with piece type and color
    Piece::Piece(Enums::PieceType piece_type, Enums::Color color)
        : piece_type_(piece_type), color_(color), has_moved_(false), has_promoted_(false) {};

    // default destructor
    Piece::~Piece() {};


    // get all positions a piece can move to from its current position (in EXACTLY ONE Direction)
    std::vector<Position> Piece::GetPositionsInDir(
        const Position& from_position, const Board& board, const Direction& direction) const
    {
        std::vector<Position> positions;

        for (Position position = from_position + direction; board.IsPositionOnBoard(position); position = position + direction)
        {
            if (board.IsPositionEmpty(position))
            {
                positions.push_back(position);
                continue;
            }

            const Piece* piece = board.GetPieceAt(position);


            if (piece->GetColor() != color_)
            {
                positions.push_back(position);
            }
            break;
        }

        return positions;
    }

    // get all positions a piece can move to from its current position (in a SET of MANY Directions)
    std::vector<Position> Piece::GetPositionsInDirs(
        const Position& from_position, const Board &board, const std::vector<Direction>& directions) const
    {
        std::vector<Position> positions;

        for (const Direction& direction : directions)
        {
            std::vector<Position> temp = GetPositionsInDir(from_position, board, direction);
            positions.insert(positions.end(), temp.begin(), temp.end());
        }

        return positions;
    }


    // mark the piece as having already moved (use for castling and pawn double step)
    void Piece::SetHasMoved()
    {
        has_moved_ = true;
    }

    // mark the piece as having already promoted (for pawns)
    void Piece::SetHasPromoted()
    {
        has_promoted_ = true;
    }


    // get the piece type of a piece (pawn, knight, bishop ...)
    Enums::PieceType Piece::GetPieceType() const
    {
        return piece_type_;
    }

    // get the color of the piece (Dark, Light, None)
    Enums::Color Piece::GetColor() const
    {
        return color_;
    }

    // returns true if piece has already moved, false otherwise
    bool Piece::HasMoved() const
    {
        return has_moved_;
    }

    // returns true if piece has already promoted, false otherwise
    bool Piece::HasPromoted() const
    {
        return has_promoted_;
    }

} // namespace GameLogic
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
    // Contruct a piece object with piece type and color
    Piece::Piece(Enums::PieceType piece_type, Enums::Color color)
        : piece_type_(piece_type), color_(color), has_moved_(false), has_promoted_(false) {};

    // Default destructor
    Piece::~Piece() {};


    // Get all positions a piece can move to from its current position (in EXACTLY ONE Direction)
    std::vector<Position> Piece::GetPositionsInDir(
        const Position& from_position, const Board& board, const Direction& direction) const
    {
        std::vector<Position> to_positions;

        for (Position to_position = from_position + direction; board.IsPositionOnBoard(to_position); to_position = to_position + direction)
        {
            // If square or position is empty, we can move the piece there
            if (board.IsPositionEmpty(to_position))
            {
                to_positions.push_back(to_position);
                continue;
            }

            const Piece* piece = board.GetPieceAt(to_position);
            // If square or position contains enemy piece we can capture.
            if (piece->GetColor() != this->color_)
            {
                to_positions.push_back(to_position);
            }

            // When enemy or ally piece is met stop scanning in this direction
            break;
        }

        return to_positions;
    }

    // Get all positions a piece can move to from its current position (in a SET of MANY Directions)
    std::vector<Position> Piece::GetPositionsInDirs(
        const Position& from_position, const Board &board, const std::vector<Direction>& directions) const
    {
        std::vector<Position> to_positions;

        for (const Direction& direction : directions)
        {
            std::vector<Position> temp = GetPositionsInDir(from_position, board, direction);
            to_positions.insert(to_positions.end(), temp.begin(), temp.end());
        }

        return to_positions;
    }


    // Mark the piece as having already moved (use for castling and pawn double step)
    void Piece::SetHasMoved()
    {
        this->has_moved_ = true;
    }

    // Mark the piece as having already promoted (for pawns)
    void Piece::SetHasPromoted()
    {
        this->has_promoted_ = true;
    }


    // Get the piece type of a piece (pawn, knight, bishop ...)
    Enums::PieceType Piece::GetPieceType() const
    {
        return this->piece_type_;
    }

    // Get the color of the piece (Dark, Light, None)
    Enums::Color Piece::GetColor() const
    {
        return this->color_;
    }

    // Returns true if piece has already moved, false otherwise
    bool Piece::HasMoved() const
    {
        return this->has_moved_;
    }

    // Returns true if piece has already promoted, false otherwise
    bool Piece::HasPromoted() const
    {
        return this->has_promoted_;
    }

} // namespace GameLogic
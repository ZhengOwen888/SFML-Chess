#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "pieces/king.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>
#include <array>

namespace GameLogic
{
	// Construct a King object with color
	King::King(Enums::Color color)
		: Piece(Enums::PieceType::King, color) {};

	// Make a clone of King object
	std::unique_ptr<Piece> King::ClonePiece() const
	{
		return std::make_unique<King>(*this);
	}

	// Get potential positions that are 1 step away from the king in the 8 cardinal directions
	std::vector<Position> King::GetPositionsFromAdjacentDirs(
		const Position& from_position, const Board& board, const std::vector<Direction>& directions) const
	{
		std::vector<Position> to_positions;

		for (const Direction& direction : directions)
		{
			Position to_position = from_position + direction;

			// Skip if the position is off the board
			if (!board.IsPositionOnBoard(to_position))
			{
				continue;
			}

			// Check if the position is empty with no piece
			if (board.IsPositionEmpty(to_position))
			{
				to_positions.push_back(to_position);
				continue;
			}

			// If square or position contains enemy piece we can capture.
			if (board.GetPieceAt(to_position)->GetColor() != this->color_)
			{
				to_positions.push_back(to_position);
			}
		}

		return to_positions;
	}

	// Get King moves from a position
    // For each adjacent position: if on board and (empty or enemy) include.
    // Castling is handled elsewhere.
	// !!! Does not check king safety
	std::vector<Move> King::GetPotentialMoves(const Position& from_position, const Board& board) const
	{
		std::vector<Position> to_positions = GetPositionsFromAdjacentDirs(from_position, board, King::AdjacentDirs);

		std::vector<Move> moves;
		moves.reserve(to_positions.size());

		for (const Position& to_position : to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}

		return moves;
	}
}
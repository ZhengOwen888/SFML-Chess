#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "pieces/knight.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	// Construct a Knight object with color
	Knight::Knight(Enums::Color color)
		: Piece(Enums::PieceType::Knight, color) {}

	// Make a clone of this Knight object
	std::unique_ptr<Piece> Knight::ClonePiece() const
	{
		return std::make_unique<Knight>(*this);
	}

	// Get all positions this Knight piece can move to from its current position
	std::vector<Position> Knight::GetPositionsFromJumpDirs(
		const Position &from_position, const Board &board, const std::vector<Direction> &directions) const
	{
		std::vector<Position> to_positions;
		to_positions.reserve(directions.size());

		for (const Direction& direction : directions)
		{
			Position to_position = from_position + direction;

			// If position is not on board check the next position
			if (!board.IsPositionOnBoard(to_position))
			{
				continue;
			}

			// If square or position is empty, we can move the piece there
			if (board.IsPositionEmpty(to_position))
			{
				to_positions.push_back(to_position);
				continue;
			}

			const Piece *piece = board.GetPieceAt(to_position);
			// If square or position contains enemy piece we can capture.
			if (piece->GetColor() != this->color_)
			{
				to_positions.push_back(to_position);
			}
		}

		return to_positions;
	}

	// Get Knight moves from a position
    // For each jump target: if on board and not friendly piece, include.
	// !!! Does not check king safety
	std::vector<Move> Knight::GetPotentialMoves(const Position& from_position, const Board& board) const
	{
		// List of positions this Knight piece can move to
		std::vector<Position> to_positions = GetPositionsFromJumpDirs(from_position, board, Knight::JumpDirs);

		// List of moves this Knight piece can make
		std::vector<Move> moves;
		moves.reserve(to_positions.size());

		for (const Position& to_position : to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}
		return moves;
	}
}
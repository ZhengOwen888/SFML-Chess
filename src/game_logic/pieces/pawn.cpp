#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "pieces/pawn.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	Pawn::Pawn(Enums::Color color)
		: Piece(Enums::PieceType::Pawn, color) {}

	std::unique_ptr<Piece> Pawn::ClonePiece() const
	{
		return std::make_unique<Pawn>(*this);
	}

	std::vector<Position> Pawn::GetForwardPositions(const Position &from_position, const Board &board) const
	{
		std::vector<Position> to_positions;
		Direction forward_direction = Forward(this->color_);

		// One step forward
		Position one_move_forward = from_position + forward_direction;

		if (!board.IsPositionOnBoard(one_move_forward) || !board.IsPositionEmpty(one_move_forward))
		{
			return to_positions; // Forward is blocked of off the board
		}
		to_positions.push_back(one_move_forward);

		// Two step forward
		Position two_move_forward = one_move_forward + forward_direction;

		// Pawn can move two squares only if it hasn't moved yet
		if (!HasMoved() && board.IsPositionOnBoard(two_move_forward) && board.IsPositionEmpty(two_move_forward))
		{
			to_positions.push_back(two_move_forward);
		}
		return to_positions;
	}

	std::vector<Position> Pawn::GetCapturePositions(const Position& from_position, const Board& board) const
	{
		std::vector<Position> to_positions;

		// Get the two possible diagonal directions a pawn can capture in
		std::vector<Direction> capture_directions = CaptureDirs(this->color_);

		for (const Direction& capture_direction : capture_directions)
		{
			Position to_position = from_position + capture_direction;

			// Skip is position is off the board or position is empty with no enemy piece
			if (!board.IsPositionOnBoard(to_position) || board.IsPositionEmpty(to_position))
			{
				continue;
			}

			// Add position if position contains an enemy piece
			if (board.GetPieceAt(to_position)->GetColor() != this->color_)
			{
				to_positions.push_back(to_position);
			}
		}

		return to_positions;
	}

	// !!! Does not check king safety
	std::vector<Move> Pawn::GetPotentialMoves(const Position& from_position, const Board& board) const
	{
		std::vector<Position> forward_to_positions = GetForwardPositions(from_position, board);
		std::vector<Position> capture_to_positions = GetCapturePositions(from_position, board);

		std::vector<Move> moves;

		for (const Position& forward_to_position : forward_to_positions)
		{
			int row_difference = std::abs(forward_to_position.GetRow() - from_position.GetRow());
			// If the pawn moves 2 steps foward then it has a move type of Double Pawn
			// Used for EnPassants
			if (row_difference == 2)
			{
				moves.push_back(Move(Enums::MoveType::DoublePawn, from_position, forward_to_position));
			}
			else
			{
				moves.push_back(Move(Enums::MoveType::Normal, from_position, forward_to_position));
			}
		}

		for (const Position& capture_to_position : capture_to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, capture_to_position));
		}

		return moves;
	}
}
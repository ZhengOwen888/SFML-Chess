#include "game_logic/base/direction.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/board.hpp"

#include "game_logic/pieces/pawn.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>
#include <cmath>

namespace GameLogic
{
	// Construct a Pawn object with color
	Pawn::Pawn(Enums::Color color)
		: Piece(Enums::PieceType::Pawn, color) {}

	// Make a clone of this Pawn object
	std::unique_ptr<Piece> Pawn::ClonePiece() const
	{
		return std::make_unique<Pawn>(*this);
	}

	// Get position in the forward direction
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

	// Get position in the forward diagonal direction
	std::vector<Position> Pawn::GetCapturePositions(const Position& from_position, const Board& board, const Move &last_move) const
	{
		std::vector<Position> to_positions;

		// Get the two possible diagonal directions a pawn can capture in
		std::vector<Direction> capture_directions = CaptureDirs(this->color_);

		for (const Direction& capture_direction : capture_directions)
		{
			Position to_position = from_position + capture_direction;

			// Skip if position is off the board
			if (!board.IsPositionOnBoard(to_position))
			{
				continue;
			}

			// Add position if position contains an enemy piece
			if (!board.IsPositionEmpty(to_position) && board.GetPieceAt(to_position)->GetColor() != this->color_)
			{
				to_positions.push_back(to_position);
			}

			// If the position is empty check if enpassant is possible
			if (CanEnPassant(from_position, to_position, board, last_move))
			{
				to_positions.push_back(to_position);
			}
		}

		return to_positions;
	}

	// Return true if pawn can EnPassant
	bool Pawn::CanEnPassant(const Position &from_position, const Position &to_position, const Board& board, const Move &last_move) const
	{
		if (last_move.GetMoveType() == Enums::MoveType::DoublePawn && board.IsPositionEmpty(to_position))
		{
			return from_position.GetRow() == last_move.GetToPosition().GetRow()
				&& to_position.GetCol()   == last_move.GetToPosition().GetCol();
		}

		return false;
	}


    // Return true is pawn can be promoted
	bool Pawn::CanPromotePawn(const Position &to_position, const Board &board) const
	{
		// if pawn's forward move is either end of the board then we know that the pawn can be promoted
		if (!board.IsPositionOnBoard(to_position))
		{
			return false;
		}
		return to_position.GetRow() == Constants::BOARD_SIZE - 1 || to_position.GetRow() == 0;
	}

	// Get pawn moves from a position (basic):
    // 1) One step forward: if empty include.
    // 2) Two steps: only if first move and both positions are empty.
    // 3) Captures: check two diagonal targets; include if enemy there.
    // 4) Promotion / en passant handled later.
    // !!! Does not check king safety
	std::vector<Move> Pawn::GetPotentialMoves(const Position& from_position, const Board& board, const Move &last_move) const
	{
		std::vector<Position> forward_to_positions = GetForwardPositions(from_position, board);
		std::vector<Position> capture_to_positions = GetCapturePositions(from_position, board, last_move);

		std::vector<Move> moves;

		// Check forward positions
		for (const Position& forward_to_position : forward_to_positions)
		{
			Enums::MoveType move_type;

			int row_difference = std::abs(forward_to_position.GetRow() - from_position.GetRow());

			// If the pawn moves 2 steps foward then it has a move type of Double Pawn
			// Used for EnPassants
			if (row_difference == 2)
			{
				move_type = Enums::MoveType::DoublePawn; // Double Forward Step
			}
			else if (CanPromotePawn(forward_to_position, board))
			{
				move_type = Enums::MoveType::PawnPromotion;
			}
			else
			{
				move_type = Enums::MoveType::Normal; // Single Forward Step
			}

			moves.push_back(Move(move_type, from_position, forward_to_position));
		}

		// Check the forward diagonal directions
		for (const Position& capture_to_position : capture_to_positions)
		{
			Enums::MoveType move_type;

			// Check if pawn can capture by EnPassant otherwise it a normal capture
			if (CanEnPassant(from_position, capture_to_position, board, last_move))
			{
				move_type = Enums::MoveType::EnPassant;
			}
			else if (CanPromotePawn(capture_to_position, board))
			{
				move_type = Enums::MoveType::PawnPromotion;
			}
			else
			{
				move_type = Enums::MoveType::Normal;
			}

			moves.push_back(Move(move_type, from_position, capture_to_position));
		}

		return moves;
	}
}


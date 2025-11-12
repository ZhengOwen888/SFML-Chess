#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "bishop.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	// Construct a Bishop object with color
	Bishop::Bishop(Enums::Color color)
		: Piece(Enums::PieceType::Bishop, color) {};

	// Make a clone of Bishop object
	std::unique_ptr<Piece> Bishop::ClonePiece() const
	{
		return std::make_unique<Bishop>(*this);
	}

	// Get bishop moves from a square
	// Steps similar to rook but only diagonal directions.
	// Walk each diagonal until off board or blocked.
    // Include first enemy then stop; stop on friendly.
	// !!! Does not check king safety
	std::vector<Move> Bishop::GetPotentialMoves(const Position& from_position, const  Board& board) const
	{
		// List of positions this Bishop piece can move to
		std::vector<Position> to_positions = GetPositionsInDirs(from_position, board, Bishop::DiagonalDirs);

		// List of moves this Bishop piece can make
		std::vector<Move> moves;
		moves.reserve(to_positions.size());

		for (const Position& to_position : to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}
		return moves;
	}
}
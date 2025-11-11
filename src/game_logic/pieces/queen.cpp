#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "queen.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	// Construct a Queen object with color
	Queen::Queen(Enums::Color color)
		: Piece(Enums::PieceType::Queen, color) {}

	// Make a clone of this Queen object
	std::unique_ptr<Piece> Queen::ClonePiece() const
	{
		return std::make_unique<Queen>(*this);
	}

	// Get queen moves from a position
    // Combine rook + bishop logic (8 directions).
    // Walk each direction until off board or blocked; include first enemy then stop.
	std::vector<Move> Queen::GetLegalMoves(const Position& from_position, const Board& board) const
	{
		// List of positions this Queen piece can move to
		std::vector<Position> to_positions = this->GetPositionsInDirs(from_position, board, Queen::AllDirs);

		// List of moves this Queen piece can make
		std::vector<Move> moves;
		moves.reserve(to_positions.size());

		for (const Position& to_position : to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}

		return moves;
	}
}
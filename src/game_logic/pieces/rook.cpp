#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "rook.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	// Construct a Rook object with color
	Rook::Rook(Enums::Color color)
		: Piece(Enums::PieceType::Rook, color) {}

	// Make a clone of this Rook object
	std::unique_ptr<Piece> Rook::ClonePiece() const
	{
		return std::make_unique<Rook>(*this);
	}

	// Get rook moves from a position
    // Steps:
    // - For each orthogonal dir, go step by step until off the board.
    // - Stop at the first piece. If enemy, include that position; if friendly, do not include it.
	std::vector<Move> Rook::GetLegalMoves(const Position& from_position, const Board& board) const
	{
		// List of positions this Rook piece can move to
		std::vector<Position> to_positions = this->GetPositionsInDirs(from_position, board, Rook::OrthogonalDirs);

		// List of moves this Rook piece can make
		std::vector<Move> moves;
		moves.reserve(to_positions.size());

		for (const Position& to_position : to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}

		return moves;
	}
}
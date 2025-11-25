#include "game_logic/base/direction.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/board.hpp"

#include "game_logic/pieces/rook.hpp"

#include "game_logic/enums.hpp"

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
	// !!! Does not check king safety
	std::vector<Move> Rook::GetPotentialMoves(
		const Position& from_position, const Board& board, const Move* last_move) const
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
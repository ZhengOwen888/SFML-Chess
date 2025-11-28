#include "game_logic/base/direction.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/board.hpp"

#include "game_logic/pieces/queen.hpp"

#include "game_logic/enums.hpp"

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
	// !!! Does not check king safety
	std::vector<Move> Queen::GetPotentialMoves(
		const Position& from_position, const Board& board, const Move* last_move) const
	{
		/** Static constant vector defining the eight cardinal directions a bishop can move in. */
        static const std::vector<Direction> AllDirs =
        {
            Direction::North,
            Direction::South,
            Direction::East,
            Direction::West,
            Direction::NorthEast,
            Direction::NorthWest,
            Direction::SouthEast,
            Direction::SouthWest
        };
		// List of positions this Queen piece can move to
		std::vector<Position> to_positions = this->GetPositionsInDirs(from_position, board, AllDirs);

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
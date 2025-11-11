#include "direction.hpp"
#include "position.hpp"
#include "move.hpp"
#include "board.hpp"
#include "king.hpp"
#include "enums.hpp"

#include <memory>
#include <vector>
#include <array>

namespace GameLogic
{
	King::King(Enums::Color color)
		: Piece(Enums::PieceType::King, color) {}

	std::unique_ptr<Piece> King::ClonePiece() const
	{
		return std::make_unique<King>(*this);
	}

	std::vector<Move> King::GetLegalMoves(const Position& from_position, const Board& board) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}
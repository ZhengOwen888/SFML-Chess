#include "pieces/king.hpp"

namespace GameLogic
{
	King::King(Enums::Color color)
		: Piece(Enums::PieceType::King, color) {}

	King::King(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::King, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> King::clonePiece() const
	{
		return std::make_unique<King>(*this);
	}

	std::vector<Move> King::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


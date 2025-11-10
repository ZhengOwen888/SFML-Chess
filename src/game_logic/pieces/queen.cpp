#include "pieces/queen.hpp"

namespace GameLogic
{
	Queen::Queen(Enums::Color color)
		: Piece(Enums::PieceType::Queen, color) {}

	Queen::Queen(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::Queen, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> Queen::clonePiece() const
	{
		return std::make_unique<Queen>(*this);
	}

	std::vector<Move> Queen::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


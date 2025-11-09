#include "pieces/knight.hpp"

namespace GameLogic
{
	Knight::Knight(Enums::Color color)
		: Piece(Enums::PieceType::Knight, color) {}

	Knight::Knight(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::Knight, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> Knight::clonePiece() const
	{
		return std::make_unique<Knight>(*this);
	}

	std::vector<Move> Knight::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


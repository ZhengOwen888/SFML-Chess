#include "pieces/bishop.hpp"

namespace GameLogic
{
	Bishop::Bishop(Enums::Color color)
		: Piece(Enums::PieceType::Bishop, color) {}

	Bishop::Bishop(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::Bishop, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> Bishop::clonePiece() const
	{
		return std::make_unique<Bishop>(*this);
	}

	std::vector<Move> Bishop::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


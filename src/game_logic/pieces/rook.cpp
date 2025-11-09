#include "pieces/rook.hpp"

namespace GameLogic
{
	Rook::Rook(Enums::Color color)
		: Piece(Enums::PieceType::Rook, color) {}

	Rook::Rook(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::Rook, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> Rook::clonePiece() const
	{
		return std::make_unique<Rook>(*this);
	}

	std::vector<Move> Rook::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


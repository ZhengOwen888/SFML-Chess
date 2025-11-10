#include "pieces/pawn.hpp"

namespace GameLogic
{
	Pawn::Pawn(Enums::Color color)
		: Piece(Enums::PieceType::Pawn, color) {}

	Pawn::Pawn(Enums::Color color, bool has_moved, bool has_promoted)
		: Piece(Enums::PieceType::Pawn, color, has_moved, has_promoted) {}

	std::unique_ptr<Piece> Pawn::clonePiece() const
	{
		return std::make_unique<Pawn>(*this);
	}

	std::vector<Move> Pawn::getLegalMoves(const Position& /*from_position*/, Board& /*board*/) const
	{
		// Will be implemented when Board occupancy APIs are available.
		return {};
	}
}


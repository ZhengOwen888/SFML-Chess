#include "game_logic/base/direction.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/board.hpp"

#include "game_logic/pieces/king.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
	// Construct a King object with color
	King::King(Enums::Color color)
		: Piece(Enums::PieceType::King, color) {};

	// Make a clone of King object
	std::unique_ptr<Piece> King::ClonePiece() const
	{
		return std::make_unique<King>(*this);
	}

	// Get potential positions that are 1 step away from the king in the 8 cardinal directions
	std::vector<Position> King::GetPositionsFromAdjacentDirs(
		const Position& from_position, const Board& board, const std::vector<Direction>& directions) const
	{
		std::vector<Position> to_positions;

		for (const Direction& direction : directions)
		{
			Position to_position = from_position + direction;

			// Skip if the position is off the board
			if (!board.IsPositionOnBoard(to_position))
			{
				continue;
			}

			// Check if the position is empty with no piece
			if (board.IsPositionEmpty(to_position))
			{
				to_positions.push_back(to_position);
				continue;
			}

			// If square or position contains enemy piece we can capture.
			if (board.GetPieceAt(to_position)->GetColor() != this->color_)
			{
				to_positions.push_back(to_position);
			}
		}

		return to_positions;
	}


	// Get potential positions for king side and queen side castling
	std::vector<Position> King::GetPositionsFromCastling(
		const Position &from_position, const Board &board) const
	{
		std::vector<Position> to_positions;

		const Piece *piece = board.GetPieceAt(from_position);

		// Check if the piece is actually a king piece
		if (piece == nullptr || piece->GetPieceType() != Enums::PieceType::King)
		{
			return {};
		}

		// Check if king side castling is possible
		const Position ks_rook_position = from_position + Direction::East *  Constants::KING_SIDE_ROOK_OFFSET;
		std::vector<Position> ks_position_in_between =
		{
			from_position + Direction::East * 1,
			from_position + Direction::East * 2
		};
		if (CanCastle(from_position, ks_rook_position, ks_position_in_between, board))
		{
			Position king_to_position = from_position + Direction::East * Constants::KING_CASTLE_MOVE_OFFSET;
			to_positions.push_back(king_to_position);
		}

		// Check if queen side castling is possible
		const Position qs_rook_position = from_position + Direction::West * Constants::QUEEN_SIDE_ROOK_OFFSET;
		std::vector<Position> qs_position_in_between =
		{
			from_position + Direction::West * 1,
			from_position + Direction::West * 2,
			from_position + Direction::West * 3
		};
		if (CanCastle(from_position, qs_rook_position, qs_position_in_between, board))
		{
			Position king_to_position = from_position + Direction::West * Constants::KING_CASTLE_MOVE_OFFSET;
			to_positions.push_back(king_to_position);
		}

		return to_positions;
	}

	// Returns true if the king can castle !!! Does not check for king safety
	bool King::CanCastle(
		const Position &king_position, const Position &rook_position,
		const std::vector<Position> &positions_in_between, const Board &board) const
	{
		const Piece *king = board.GetPieceAt(king_position);
		const Piece *rook = board.GetPieceAt(rook_position);

		// Returns false if there is no piece in the king's positiont and rook's position
		if (king == nullptr || rook == nullptr)
		{
			return false;
		}

		// Returns false if the type of the pieces are not king and rook
		if (king->GetPieceType() != Enums::PieceType::King || rook->GetPieceType() != Enums::PieceType::Rook)
		{
			return false;
		}

		// Returns false if the king or the rook has already moved
		if (king->HasMoved() || rook->HasMoved())
		{
			return false;
		}

		// Returns false if !!!ANY position between king and rook is !!!NOT empty
		if (!board.ArePositionsEmpty(positions_in_between))
		{
			return false;
		}

		return true;
	}

	// Get King moves from a position
    // For each adjacent position: if on board and (empty or enemy) include.
    // Castling is handled elsewhere.
	// !!! Does not check king safety
	std::vector<Move> King::GetPotentialMoves(
		const Position& from_position, const Board& board, const Move* last_move) const
	{
		std::vector<Position> adjacent_to_positions = GetPositionsFromAdjacentDirs(from_position, board, King::AdjacentDirs);
		std::vector<Position> castle_to_positions = GetPositionsFromCastling(from_position, board);
		std::vector<Move> moves;

		for (const Position& to_position : adjacent_to_positions)
		{
			moves.push_back(Move(Enums::MoveType::Normal, from_position, to_position));
		}

		for (const Position& to_position : castle_to_positions)
		{
			Position king_side_to_position = from_position + Direction::East * 2;
			Position queen_side_to_position = from_position + Direction::West * 2;

			Enums::MoveType move_type;

			if (to_position == king_side_to_position)
			{
				move_type = Enums::MoveType::CastleKS;
			}
			else if (to_position == queen_side_to_position)
			{
				move_type = Enums::MoveType::CastleQS;
			}
			else {
				move_type = Enums::MoveType::Normal;
			}

			moves.push_back(Move(move_type, from_position, to_position));
		}

		return moves;
	}
}
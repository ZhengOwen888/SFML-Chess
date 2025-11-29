#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <stdexcept>

namespace GameLogic
{
    // Construct a Move object with move type, from position and to position
    Move::Move(Enums::MoveType move_type, const Position &from_position, const Position &to_position)
        : move_type_(move_type), from_position_(from_position), to_position_(to_position), promotion_piece_type_(Enums::PieceType::None) {};

    // Returns true if move type, start, and destination are equal
    bool Move::operator==(const Move& other_move) const
    {
        return this->move_type_ == other_move.move_type_
            && this->from_position_ == other_move.from_position_
            && this->to_position_ == other_move.to_position_;
    }

    void Move::SetPromotionPieceType(Enums::PieceType promotion_piece_type)
    {
        if (promotion_piece_type == Enums::PieceType::King || promotion_piece_type == Enums::PieceType::Pawn)
        {
            throw std::invalid_argument("Invalid promotion piece type: King or Pawn.");
        }
        this->promotion_piece_type_ = promotion_piece_type;
    }

    std::tuple<Position, Position, Enums::PieceType> Move::FromUCI(const std::string &uci_string)
    {
        if (uci_string.size() < 4 || uci_string.size() > 5)
        {
            throw std::invalid_argument("Invalid UCI move: " + uci_string);
        }

        char from_file = uci_string.at(0);
        char from_rank = uci_string.at(1);
        Position from_position = Position::AlgebraicToPosition(from_file, from_rank);

        char to_file = uci_string.at(2);
        char to_rank = uci_string.at(3);
        Position to_position = Position::AlgebraicToPosition(to_file, to_rank);

        char promotion_type = uci_string.size() == 5 ? uci_string.at(5) : '\0';
        Enums::PieceType promotion_piece_type;

        switch (std::tolower(promotion_type))
        {
            case ('b'):
                promotion_piece_type = Enums::PieceType::Bishop;
                break;
            case ('n'):
                promotion_piece_type = Enums::PieceType::Knight;
                break;
            case ('r'):
                promotion_piece_type = Enums::PieceType::Rook;
                break;
            case ('q'):
                promotion_piece_type = Enums::PieceType::Queen;
                break;
            default:
                promotion_piece_type = Enums::PieceType::None;
                break;
        }

        return std::make_tuple(from_position, to_position, promotion_piece_type);
    }

    // Return the type of the move (Normal, KSCastle, QSCastle ...)
    Enums::MoveType Move::GetMoveType() const
    {
        return this->move_type_;
    }

    // Return the position the piece is moving from
    const Position& Move::GetFromPosition() const
    {
        return this->from_position_;
    }

    // Return the position the piece is moving to
    const Position& Move::GetToPosition() const
    {
        return this->to_position_;
    }

} // namespace GameLogic
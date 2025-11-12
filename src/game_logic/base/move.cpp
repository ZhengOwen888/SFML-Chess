#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"

#include "game_logic/enums.hpp"

#include <memory>

namespace GameLogic
{
    // Construct a Move object with move type, from position and to position
    Move::Move(Enums::MoveType move_type, const Position &from_position, const Position &to_position)
        : move_type_(move_type), from_position_(from_position), to_position_(to_position) {};

    Move::~Move() {};

    // Returns true if both moves have the same from and to position
    bool Move::operator==(const Move& other_move) const
    {
        return this->from_position_ == other_move.from_position_
            && this->to_position_ == other_move.to_position_;
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
#include "move.hpp"
#include "position.hpp"
#include "enums.hpp"

#include <memory>

namespace GameLogic
{
    // construct a Move object with move type, from position and to position
    Move::Move(Enums::MoveType move_type, const Position &from_position, const Position &to_position)
        : move_type_(move_type), from_position_(from_position), to_position_(to_position) {};

    Move::~Move() {};

    // return the type of the move (Normal, KSCastle, QSCastle ...)
    Enums::MoveType Move::GetMoveType() const
    {
        return move_type_;
    }

    // return the position the piece is moving from
    const Position& Move::GetFromPos() const
    {
        return from_position_;
    }

    // return the position the piece is moving to
    const Position& Move::GetToPos() const
    {
        return to_position_;
    }

} // namespace GameLogic
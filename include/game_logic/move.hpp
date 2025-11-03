#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include "position.hpp"
#include "enums.hpp"

#include <memory>

namespace GameLogic
{
    class Move
    {
        public:
            // contructor a Move object with move type, start position and destination position
            Move(Enums::MoveType move_type, const Position&  from_position, const Position& to_position);
            ~Move();

            // getters
            Enums::MoveType GetMoveType() const;
            const Position& GetFromPos() const;
            const Position& GetToPos() const;

        private:
            Enums::MoveType move_type_;
            Position from_position_;
            Position to_position_;
    };
} // namespace GameLogic

#endif
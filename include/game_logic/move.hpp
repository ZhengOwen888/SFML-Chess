#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include <array>
#include <memory>

#include "board.hpp"
#include "position.hpp"

#include "enums.hpp"

namespace GameLogic
{
    class Move
    {
        public:
            Move(Enums::MoveType move_type,Position from_position, Position to_position);
            ~Move();

            virtual void executeMove(Board &board_) = 0;

            Position getFromPos() const;
            Position getToPos() const;

        private:
            Enums::MoveType move_type_;
            Position from_position_;
            Position to_position_;
    };
}

#endif
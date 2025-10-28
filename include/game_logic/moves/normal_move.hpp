#ifndef GAMELOGIC_NORMAL_MOVE_HPP
#define GAMELOGIC_NORMAL_MOVE_HPP

#include "board.hpp"
#include "move.hpp"
#include "position.hpp"

namespace GameLogic
{
    class NormalMove: public Move
    {
        public:
            NormalMove(Position from_position, Position to_position);
            ~NormalMove();

            void executeMove(Board::Grid &grid_) override;
    };
}

#endif
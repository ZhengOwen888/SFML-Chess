#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include <memory>

#include "board.hpp"
#include "position.hpp"

#include "enums.hpp"

namespace GameLogic
{
    class Move
    {
        public:
            // contructors and destructors
            Move(Enums::MoveType move_type, Position&  from_position, Position& to_position);
            virtual ~Move() = default;

            // execute given move on board
            virtual void executeMove(Board& board) = 0;

            // Getters
            Enums::MoveType getMoveType() const;
            const Position& getFromPos() const;
            const Position& getToPos() const;

        private:
            Enums::MoveType move_type_;
            Position from_position_;
            Position to_position_;
    };
} // namespace GameLogic

#endif
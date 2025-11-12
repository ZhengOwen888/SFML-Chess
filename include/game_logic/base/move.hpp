#ifndef GAMELOGIC_MOVE_HPP
#define GAMELOGIC_MOVE_HPP

#include "game_logic/base/position.hpp"

#include "game_logic/enums.hpp"

#include <memory>

namespace GameLogic
{
    class Move
    {
        public:
            // Contructor a Move object with move type, start position and destination position
            Move(Enums::MoveType move_type, const Position&  from_position, const Position& to_position);
            ~Move();

            // Returns true if both moves have the same from and to position
            bool operator==(const Move &other_move) const;

            // Getters
            Enums::MoveType GetMoveType() const;
            const Position& GetFromPosition() const;
            const Position& GetToPosition() const;

        private:
            Enums::MoveType move_type_;
            Position from_position_;
            Position to_position_;
    };
} // namespace GameLogic

#endif
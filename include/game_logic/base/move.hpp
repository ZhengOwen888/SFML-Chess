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
            Move() = default;
            /**
             * @brief Contruct a chess Move
             * @param move_type Type of move (Normal, DoublePawn, CastleKS, CastleQS ...)
             * @param from_position Starting position
             * @param to_position Destination position
             */
            Move(Enums::MoveType move_type, const Position&  from_position, const Position& to_position);
            ~Move() = default;



            /** @return true if both moves have equal move type, start position, and destination position */
            bool operator==(const Move &other_move) const;

            /** @return the move type of the move */
            Enums::MoveType GetMoveType() const;

            /** @return the start position of the move */
            const Position& GetFromPosition() const;

            /** @return the destination position of the move */
            const Position& GetToPosition() const;

        private:
            Enums::MoveType move_type_;
            Position from_position_;
            Position to_position_;
    };
} // namespace GameLogic

#endif
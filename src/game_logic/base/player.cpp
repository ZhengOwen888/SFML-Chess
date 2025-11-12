#include "game_logic/base/player.hpp"

#include "game_logic/enums.hpp"

namespace GameLogic
{
    Player::Player(Enums::Color color)
        : color_(color) {};

    Player::~Player() {};

    Enums::Color Player::GetColor() const
    {
        return this->color_;
    }
} // namespace GameLogic
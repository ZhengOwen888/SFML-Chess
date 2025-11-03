#include "player.hpp"
#include "enums.hpp"

namespace GameLogic
{
    Player::Player(Enums::Color color)
        : color_(color) {};

    Player::~Player() {};

    Enums::Color Player::GetColor() const
    {
        return color_;
    }
} // namespace GameLogic
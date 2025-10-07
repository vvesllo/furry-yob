#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
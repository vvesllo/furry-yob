#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

// sniper
class Enemy003 : public Entity
{
private:
    sf::Vector2f m_distance;

public:
    Enemy003(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
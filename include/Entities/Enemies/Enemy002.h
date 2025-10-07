#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

// streetcleaner ultrakill no way
class Enemy002 : public Entity
{
private:
    bool m_shooting;
    float m_fire_tick;

public:
    Enemy002(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
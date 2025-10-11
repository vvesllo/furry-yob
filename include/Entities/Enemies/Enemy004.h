#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"


// gutterman from ultrakill omg
class Enemy004 : public Entity
{
private:
    sf::Vector2f m_distance;
    float m_fire_tick;

public:
    Enemy004(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
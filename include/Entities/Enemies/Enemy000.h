#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"


// soldier
class Enemy000 : public Entity
{
private:
    sf::Vector2f m_distance;

public:
    Enemy000(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
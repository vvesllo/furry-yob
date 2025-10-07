#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

// shotgun man idk
class Enemy001 : public Entity
{
private:
    sf::Vector2f m_distance;
    
public:
    Enemy001(const sf::Vector2f& position);

    void AI(const float& dt) override;
    const std::optional<LookingDirection> processDirection() override;
};
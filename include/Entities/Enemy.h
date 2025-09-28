#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Enemy : public Entity
{
private:
    bool m_staying;
    float m_shoot_cooldown;

public:
    Enemy(const sf::Vector2f& position);
    ~Enemy();

    void AI(const float& dt) override;
};
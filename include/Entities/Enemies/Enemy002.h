#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Enemy002 : public Entity
{
private:
    bool m_shooting;
    float m_shoot_cooldown;
    float m_fire_tick;

public:
    Enemy002(const sf::Vector2f& position);
    ~Enemy002();

    void AI(const float& dt) override;
};
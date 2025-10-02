#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Enemy004 : public Entity
{
private:
    bool m_staying;
    float m_shoot_cooldown;
    float m_fire_tick;

public:
    Enemy004(const sf::Vector2f& position);
    ~Enemy004();

    void AI(const float& dt) override;
};
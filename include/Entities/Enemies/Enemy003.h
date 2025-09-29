#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Enemy003 : public Entity
{
private:
    bool m_staying;
    float m_shoot_cooldown;

public:
    Enemy003(const sf::Vector2f& position);
    ~Enemy003();

    void AI(const float& dt) override;
};
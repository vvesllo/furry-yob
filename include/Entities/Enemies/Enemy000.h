#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Enemy000 : public Entity
{
private:
    bool m_staying;
    float m_shoot_cooldown;

public:
    Enemy000(const sf::Vector2f& position);
    ~Enemy000();

    void AI(const float& dt) override;
};
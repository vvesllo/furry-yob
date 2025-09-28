#pragma once

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Enemy001 : public Entity
{
private:
    bool m_staying;
    float m_shoot_cooldown;

public:
    Enemy001(const sf::Vector2f& position);
    ~Enemy001();

    void AI(const float& dt) override;
};
#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    float m_shoot_cooldown;

public:
    Player(const sf::Vector2f& position);
    ~Player();

    void AI(const float& dt) override;
};
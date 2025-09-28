#pragma once

#include <SFML/Graphics.hpp>

#include "../Core/DynamicBody.h"


enum class ProjectileType {
    Friendly,
    Hostile
};


class Projectile : public DynamicBody
{
private:
    sf::Vector2f m_direction;
    float m_life_time;
    
    ProjectileType m_type;
    DynamicBody* m_sender;
    
public:
    Projectile(const sf::Vector2f& position, DynamicBody* sender, const ProjectileType type, const sf::Vector2f& direction);
    ~Projectile();
    
    
    void AI(const float& dt) override;
    void update(const float& dt) override;
    
    
    const ProjectileType getType();
};
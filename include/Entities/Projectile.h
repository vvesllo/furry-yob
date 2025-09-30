#pragma once

#include <SFML/Graphics.hpp>

#include "../Core/DynamicBody.h"
#include "Entity.h"



class Projectile : public DynamicBody
{
private:
    sf::Vector2f m_direction;
    float m_life_time;
    const bool m_piercing;
    
    DynamicBody* m_sender;
    
public:
    Projectile(
        DynamicBody* sender,
        const sf::FloatRect& rect, 
        const std::string& texture_name,
        const sf::Vector2f& direction,
        const float& life_time,
        const bool& piercing
    );
    ~Projectile();
    
    
    void AI(const float& dt) override;
    void update(const float& dt) override;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "DynamicBody.h"
#include "Entity.h"




class Projectile : public DynamicBody
{
private:
    sf::Vector2f m_direction;
    float m_life_time;
    const bool m_piercing;
    
    DynamicBody* m_sender;
    std::function<void(Projectile*)> m_ai;
    
    void checkHit();

public:
    Projectile(
        DynamicBody* sender,
        const sf::FloatRect& rect, 
        const std::string& texture_name,
        const sf::Vector2f& direction,
        const float& life_time,
        const bool& piercing,
        std::function<void(Projectile*)> ai
    );
    ~Projectile();
    
    
    void AI(const float& dt) override;
    void update(const float& dt) override;
};
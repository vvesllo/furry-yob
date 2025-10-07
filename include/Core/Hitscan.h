#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicBody.h"


class Hitscan
{
private:
    sf::Vector2f m_direction;
    const bool m_piercing;
    
    DynamicBody* m_sender;

    sf::VertexArray m_line;

    float m_max_life_time;
    float m_life_time;
    
    void shoot(const sf::Vector2f& direction);
    
    bool rayIntersectsAABB(
        const sf::Vector2f& ray_origin, 
        const sf::Vector2f& ray_direction, 
        const sf::FloatRect& aabb,
        float& t
    );

public:
    Hitscan(
        DynamicBody* sender,
        const sf::Vector2f& position,
        const sf::Vector2f& direction,
        const bool& piercing
    );
    ~Hitscan();
    
    void update(const float& dt);

    void draw(std::unique_ptr<sf::RenderWindow>& target);

    bool isActive();
};
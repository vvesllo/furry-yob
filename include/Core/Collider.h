#pragma once

#include <SFML/Graphics.hpp>

enum class ColliderType {
    Empty,
    Ground
};

class Collider
{
private:
    sf::FloatRect m_rect;
    const ColliderType m_type;


public:
    Collider(const sf::FloatRect& rect, const ColliderType& type);

    const sf::FloatRect& getRect();
    const ColliderType& getType();
};
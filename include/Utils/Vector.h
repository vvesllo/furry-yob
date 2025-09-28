#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace VectorUtils
{
    const sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float& t);    
}
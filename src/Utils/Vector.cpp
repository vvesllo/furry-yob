#include "include/Utils/Vector.h"


const sf::Vector2f VectorUtils::lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float& t)
{
    return sf::Vector2f{
        std::lerp(a.x, b.x, t),
        std::lerp(a.y, b.y, t)
    };
}

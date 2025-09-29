#include "../../include/Core/Collider.h"



Collider::Collider(const sf::FloatRect& rect, const ColliderType& type)
    : m_rect(rect), m_type(type)
{

}

const sf::FloatRect& Collider::getRect()
{
    return m_rect;
}

const ColliderType& Collider::getType()
{
    return m_type;
}
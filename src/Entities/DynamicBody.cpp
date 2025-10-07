#include "include/Entities/DynamicBody.h"
#include "include/Core/Managers/ResourceManager.h"
#include "include/Utils/Vector.h"


DynamicBody::DynamicBody(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect)
    : m_color(color)
{
    sprite = std::make_unique<sf::Sprite>(*ResourceManager::getInstance().getTexture(texture_name));
    sprite->setOrigin(sprite->getGlobalBounds().size / 2.f);
    sprite->setColor(color);

    this->rect = rect;
    this->rect.position -= this->rect.size / 2.f;

    m_is_active = true;
}

void DynamicBody::update(const float& dt)
{
    AI(dt);
}

void DynamicBody::draw(std::unique_ptr<sf::RenderWindow>& target)
{
    /*
    sf::RectangleShape _rect(rect.size);
    _rect.setPosition(rect.position);
    _rect.setFillColor(sf::Color::Magenta);
    
    target->draw(_rect);
    */
   
    target->draw(*sprite);
}

const sf::Vector2f DynamicBody::getCenter()
{
    return rect.getCenter();
}

const sf::FloatRect DynamicBody::getRect()
{
    return rect;
}

void DynamicBody::preDestroy()
{}

void DynamicBody::destroy()
{
    preDestroy();
    m_is_active = false;
}

const bool DynamicBody::isActive()
{
    return m_is_active;
}

const sf::Color DynamicBody::getColor()
{
    return m_color;
}
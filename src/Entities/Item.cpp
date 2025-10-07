#include "include/Entities/Item.h"
#include "include/Core/Managers/ThemeManager.h"


Item::Item(const std::string& texture_name, const sf::FloatRect& rect, const ItemManager::ItemType& type) 
    : DynamicBody(
        texture_name, 
        ThemeManager::getInstance().getTheme().player,
        rect),
    m_type{ type }
{
    m_moving_time = 0;
}

Item::~Item()
{

}

void Item::AI(const float& dt)
{
    // idk
}

void Item::update(const float& dt)
{
    m_moving_time += dt; 
    sprite->setPosition(rect.position + sf::Vector2f{ 0.f, 5.f * std::sin(10.f * m_moving_time) });
}

const ItemManager::ItemType& Item::getType()
{
    return m_type;
}
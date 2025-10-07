#pragma once

#include "DynamicBody.h"
#include "../Core/Managers/ItemManager.h"



class Item : public DynamicBody
{
private:
    const ItemManager::ItemType m_type;
    float m_moving_time;

public:
    Item(const std::string& texture_name, const sf::FloatRect& rect, const ItemManager::ItemType& type);
    ~Item();
    
    void AI(const float& dt) override;
    void update(const float& dt) override;

    const ItemManager::ItemType& getType();
};
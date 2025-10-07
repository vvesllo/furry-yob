#include "include/Core/Managers/ItemManager.h"
#include "include/Entities/Entity.h"


ItemManager::ItemManager()
{
    m_item_functions[ItemType::Adrenaline] = [=](Entity* entity, const size_t& amount) {
        entity->entity_data.shot_delay = entity->m_static_entity_data.shot_delay * itemScaling(ItemScalingType::Hyperbolic, amount, 0.10f); // 10% proc chance
    };
    m_item_functions[ItemType::Feather] = [=](Entity* entity, const size_t& amount) {
        entity->entity_data.speed = entity->m_static_entity_data.speed * (1 + itemScaling(ItemScalingType::Linear, amount, 0.10f)); // 10% proc chance
    };
    /*
    m_item_functions[ItemType::Adrenaline] = [=](Entity* entity, const size_t& amount) {
        entity->entity_data.speed = entity->m_static_entity_data.speed * itemScaling(ItemScalingType::Linear, amount, 0.10f); // 10% proc chance
    };
    */
}

ItemManager& ItemManager::getInstance()
{
	static ItemManager instance;
	return instance;
}

void ItemManager::update(Entity* entity, const size_t& amount, const ItemType& type)
{
    m_item_functions[type](entity, amount);
}

float ItemManager::itemScaling(const ItemScalingType& scaling_type, const size_t& amount, const float& multiplier)
{
    switch (scaling_type)
    {
    case ItemScalingType::Hyperbolic: return 1.f / (1.f + amount * multiplier);
    case ItemScalingType::Linear:
    default: return amount * multiplier;
    }
}

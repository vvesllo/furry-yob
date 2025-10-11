#include "include/Core/Managers/ItemManager.h"
#include "include/Entities/Entity.h"


  
void ItemManager::initItems()
{
    m_items[ItemType::Adrenaline] = std::make_unique<ItemData>(
        "adrenaline",
        [this](Entity* entity, const size_t& amount) {
            entity->entity_data.shot_delay = entity->m_static_entity_data.shot_delay * hyperbolicScale(amount, 0.10f);
        }
    );

    m_items[ItemType::Feather] = std::make_unique<ItemData>(
        "feather",
        [this](Entity* entity, const size_t& amount) {
            entity->entity_data.speed = entity->m_static_entity_data.speed * (1.f + linearScale(amount, 0.10f));
        }
    );
}

ItemManager::ItemManager()
{
}

ItemManager& ItemManager::getInstance()
{
	static ItemManager instance;
	return instance;
}

std::map<ItemManager::ItemType, std::unique_ptr<ItemManager::ItemData>>& ItemManager::getItems()
{
    return m_items;
}

inline const float ItemManager::hyperbolicScale(const size_t& amount, const float& multiplier)
{
    return 1.f / (1.f + amount * multiplier);
}

inline const float ItemManager::linearScale(const size_t& amount, const float& multiplier)
{
    return amount * multiplier;
}

void ItemManager::update(Entity* entity, const ItemType& type, const size_t& amount)
{
    m_items[type]->function(entity, amount );
}

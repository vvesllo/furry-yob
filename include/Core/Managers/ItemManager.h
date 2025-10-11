#pragma once

#include <functional>
#include <string>
#include <memory>
#include <map>

class Entity;

class ItemManager
{
public:
    enum class ItemType : short
    {
        Adrenaline,
        Feather
    };

    struct ItemData {
        const std::string texture_name;
        std::function<void(Entity*, const size_t&)> function;
    };

    ItemManager();

    ItemManager(const ItemManager& other) = delete;
    ItemManager& operator=(const ItemManager& other) = delete;
	static ItemManager& getInstance();

    std::map<ItemType, std::unique_ptr<ItemData>>& getItems();
    void update(Entity* entity, const ItemType& type, const size_t& amount);

private:

    std::map<ItemType, std::unique_ptr<ItemData>> m_items;
    
    void initItems();

    inline const float hyperbolicScale(const size_t& amount, const float& multiplier);    
    inline const float linearScale(const size_t& amount, const float& multiplier);
};

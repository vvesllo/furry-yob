#pragma once

#include <map>
#include <functional>

class Entity;

class ItemManager
{
private:

    enum class ItemScalingType : short
    {
        Linear,
        Hyperbolic,
    };
    
    float itemScaling(const ItemScalingType& scaling_type, const size_t& amount, const float& chance); 
    
public:
    enum class ItemType : short
    {
        Syringe
    };

    ItemManager();

    ItemManager(const ItemManager& other) = delete;
    ItemManager& operator=(const ItemManager& other) = delete;
	static ItemManager& getInstance();

    void update(Entity* entity, const size_t& amount, const ItemType& type);

private:
    std::map<ItemType, std::function<void(Entity*, const size_t&)>> m_item_functions;
};

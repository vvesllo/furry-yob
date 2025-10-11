#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "../Hitscan.h"

#include "../../Entities/DynamicBody.h"
#include "../../Entities/Projectile.h"
#include "../../Entities/Entity.h"
#include "../../Entities/Item.h"

#include "ItemManager.h"
#include "../../Utils/Types.h"

class EntityManager
{
private:
    Types::uptr_vec<DynamicBody> m_entities;
    Types::uptr_vec<DynamicBody> m_projectiles;
    Types::uptr_vec<Hitscan> m_hitscans;

    // item :: amount
    std::map<ItemManager::ItemType, size_t> m_entity_inventory;

    void forEachUpdate(Types::uptr_vec<DynamicBody>& dynamic_bodies, const float& dt);
    void forEachDraw(Types::uptr_vec<DynamicBody>& dynamic_bodies, std::unique_ptr<sf::RenderWindow>& target);

public:

	EntityManager();

	EntityManager(const EntityManager& other) = delete;
	EntityManager& operator=(const EntityManager& other) = delete;

    static EntityManager& getInstance();
    

    void update(const float& dt);
    void draw(std::unique_ptr<sf::RenderWindow>& target);


    template<class T> requires std::is_base_of_v<Entity, T>
    void newEntity(const sf::Vector2f& position)
    {
        m_entities.emplace_back(std::make_unique<T>(position));
    }

    void newProjectile(
        DynamicBody* sender,
        const std::string& texture_name,
        const sf::FloatRect& rect,
        const sf::Vector2f& direction,
        const float& speed,
        const float& life_time,
        const bool piercing,
        std::function<void(Projectile*)> ai
    );

    void newHitscan(
        DynamicBody* sender,
        const sf::Vector2f& position,
        const sf::Vector2f& direction,
        const bool piercing);

        
    std::map<ItemManager::ItemType, size_t>& getEntityItems();
    Types::uptr_vec<DynamicBody>& getEntities();
    Types::uptr_vec<DynamicBody>& getProjectiles();

    template<class T>
    Types::uptr_ref_opt<DynamicBody> findByClass();
    Types::uptr_ref_opt<DynamicBody> findEntityByType(const EntityType& type);
};
#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "DynamicBody.h"
#include "../Entities/Projectile.h"
#include "../Entities/Entity.h"


class EntityManager
{
private:
    std::vector<std::unique_ptr<DynamicBody>> m_entities;
    std::vector<std::unique_ptr<DynamicBody>> m_projectiles;

    void forEachUpdate(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, const float& dt);
    void forEachDraw(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, std::unique_ptr<sf::RenderWindow>& target);

public:
	EntityManager();

	EntityManager(const EntityManager& other) = delete;
	EntityManager& operator=(const EntityManager& other) = delete;

	static EntityManager& getInstance();

    template<class TEntity>
    void newEntity(const sf::Vector2f& position)
    {
        m_entities.emplace_back(std::make_unique<TEntity>(position));
    }

    void newProjectile(
        DynamicBody* sender,
        const ProjectileType type,
        const sf::Vector2f& position,
        const sf::Vector2f& direction,
        const float& speed);

    void update(const float& dt);
    void draw(std::unique_ptr<sf::RenderWindow>& target);

    std::vector<std::unique_ptr<DynamicBody>>& getEntities();
    std::vector<std::unique_ptr<DynamicBody>>& getProjectiles();
    
    template<class T>
    std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>> findByClass();
    std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>> findEntityByType(const EntityType& type);
};
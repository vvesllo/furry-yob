#include "../../include/Core/EntityManager.h"
#include "../../include/Core/ResourceManager.h"

#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Player.h"

#include <fstream>

EntityManager::EntityManager()
{
}

EntityManager& EntityManager::getInstance()
{
    static EntityManager instance;
    return instance;
}

void EntityManager::newProjectile(
    DynamicBody* sender,
    const ProjectileType type,
    const sf::Vector2f& position,
    const sf::Vector2f& direction,
    const float& speed)
{
    m_projectiles.emplace_back(
        std::make_unique<Projectile>(
            position,
            sender,
            type,
            direction * speed
        )
    );
}

void EntityManager::forEachUpdate(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, const float& dt)
{
	for (size_t i=0; i < dynamic_bodies.size(); )
	{
		if (!dynamic_bodies[i]->isActive())
		{
			dynamic_bodies.erase(dynamic_bodies.begin() + i);
			continue;
		}
		dynamic_bodies[i]->update(dt);
		++i;
	}
}

void EntityManager::forEachDraw(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, std::unique_ptr<sf::RenderWindow>& target)
{
    for (const auto& dynamic_body : dynamic_bodies)
    {
        dynamic_body->draw(target);
    }
}

void EntityManager::update(const float& dt)
{
    forEachUpdate(m_entities, dt);
    forEachUpdate(m_projectiles, dt);
}

void EntityManager::draw(std::unique_ptr<sf::RenderWindow>& target)
{
    forEachDraw(m_entities, target);
    forEachDraw(m_projectiles, target);
}

std::vector<std::unique_ptr<DynamicBody>>& EntityManager::getEntities()
{
    return m_entities;
}

std::vector<std::unique_ptr<DynamicBody>>& EntityManager::getProjectiles()
{
    return m_projectiles;
}

template<class T>
std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>> EntityManager::findByClass()
{    
    for (int target_index = 0; target_index < m_entities.size(); ++target_index)
    {
        if (dynamic_cast<const T*>(m_entities[target_index].get()) != nullptr)
            return m_entities[target_index];
    }

    return nullptr;
}

std::optional<std::reference_wrapper<std::unique_ptr<DynamicBody>>> EntityManager::findEntityByType(const EntityType& type)
{
    for (int target_index = 0; target_index < m_entities.size(); ++target_index)
    {
        if (((Entity*)m_entities[target_index].get())->getType() == type) 
        {
            return m_entities[target_index];
        }
    }

    return std::nullopt;
}
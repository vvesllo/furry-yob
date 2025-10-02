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
    const std::string& texture_name,
    const sf::FloatRect& rect,
    const sf::Vector2f& direction,
    const float& speed,
    const float& life_time,
    const bool piercing,
    std::function<void(Projectile*)> ai
)
{
    m_projectiles.emplace_back(
        std::make_unique<Projectile>(
            sender,
            rect,
            texture_name,
            direction * speed,
            life_time,
            piercing,
            ai
        )
    );
}


void EntityManager::newHitscan(
    DynamicBody* sender,
    const sf::Vector2f& position,
    const sf::Vector2f& direction,
    const bool piercing)
{
    m_hitscans.emplace_back(
        std::make_unique<Hitscan>(
            sender,
            position,
            direction,
            piercing
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
    
    for (int i=0; i < m_hitscans.size(); )
    {
        if (m_hitscans[i]->isActive())
        {
            m_hitscans[i]->update(dt);
            ++i;
        }
        else
        {   
            m_hitscans.erase(m_hitscans.begin() + i);
        }
    }
}

void EntityManager::draw(std::unique_ptr<sf::RenderWindow>& target)
{
    forEachDraw(m_entities, target);
    forEachDraw(m_projectiles, target);

    for (int i=0; i < m_hitscans.size(); ++i)
    {
        m_hitscans[i]->draw(target);
    }
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
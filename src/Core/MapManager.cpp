#include "../../include/Core/MapManager.h"
#include "../../include/Core/ResourceManager.h"

#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Player.h"
#include "../../include/Entities/Enemy.h"
#include "../../include/Entities/Projectile.h"

#include <fstream>

MapManager::MapManager()
{
    m_tile_sprite = std::make_unique<sf::Sprite>(*ResourceManager::getInstance().getTexture("tile"));
    m_tile_sprite->setColor(sf::Color::Blue);
    m_size = { 25, 25 };
    m_map = {};
}

MapManager& MapManager::getInstance()
{
    static MapManager instance;
    return instance;
}

void MapManager::loadMap(const std::string& name)
{
    std::ifstream file("resources/maps/" + name + ".txt");
    std::string line;

    while (file >> line)
    {
        m_map.emplace_back(line);
    }

    file.close();
}

const std::vector<std::string>& MapManager::getMap()
{
    return m_map;
}

const sf::Vector2u& MapManager::getSize()
{
    return m_size;
}

std::unique_ptr<sf::Sprite>& MapManager::getTileSprite()
{
    return m_tile_sprite;
}   

template<>
void MapManager::newEntity<Player>(const sf::Vector2f& position)
{
    m_entities.emplace_back(std::make_unique<Player>(position));
}

template<>
void MapManager::newEntity<Enemy>(const sf::Vector2f& position)
{
    m_entities.emplace_back(std::make_unique<Enemy>(position));
}

void MapManager::newProjectile(
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

void MapManager::forEachUpdate(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, const float& dt)
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

void MapManager::forEachDraw(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, std::unique_ptr<sf::RenderWindow>& target)
{
    for (const auto& dynamic_body : dynamic_bodies)
    {
        dynamic_body->draw(target);
    }
}

void MapManager::update(const float& dt)
{
    forEachUpdate(m_entities, dt);
    forEachUpdate(m_projectiles, dt);
}

void MapManager::draw(std::unique_ptr<sf::RenderWindow>& target)
{
    forEachDraw(m_entities, target);
    forEachDraw(m_projectiles, target);
}

std::vector<std::unique_ptr<DynamicBody>>& MapManager::getEntities()
{
    return m_entities;
}

std::vector<std::unique_ptr<DynamicBody>>& MapManager::getProjectiles()
{
    return m_projectiles;
}


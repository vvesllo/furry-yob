#pragma once

#include <SFML/Graphics.hpp>

#include "DynamicBody.h"
#include "../Entities/Projectile.h"

class MapManager
{
private: 
    sf::Vector2u m_size;
    std::vector<std::string> m_map;
    std::unique_ptr<sf::Sprite> m_tile_sprite;
    std::vector<std::unique_ptr<DynamicBody>> m_entities;
    std::vector<std::unique_ptr<DynamicBody>> m_projectiles;

    void forEachUpdate(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, const float& dt);
    void forEachDraw(std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies, std::unique_ptr<sf::RenderWindow>& target);

public:
	MapManager();

	MapManager(const MapManager& other) = delete;
	MapManager& operator=(const MapManager& other) = delete;

	static MapManager& getInstance();

    void loadMap(const std::string& name);
    const std::vector<std::string>& getMap();

    template<class TEntity>
    void newEntity(const sf::Vector2f& position);

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

    const sf::Vector2u& getSize();
    std::unique_ptr<sf::Sprite>& getTileSprite();
};
#pragma once

#include <SFML/Graphics.hpp>

#include "DynamicBody.h"
#include "../Entities/Projectile.h"

class LevelManager
{
private: 
    sf::Vector2u m_size;
    std::vector<std::string> m_level;
    std::unique_ptr<sf::Sprite> m_tile_sprite;

public:
	LevelManager();

	LevelManager(const LevelManager& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;

	static LevelManager& getInstance();

    void load(const std::string& name);
    const std::vector<std::string>& get();

    const sf::Vector2u& getSize();
    std::unique_ptr<sf::Sprite>& getTileSprite();
};
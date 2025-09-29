#include "../../include/Core/ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadTexture("player", "resources/player.png");
	loadTexture("tile", "resources/tile.png");
	
	loadTexture("enemy_000", "resources/enemies/enemy_000.png");
	loadTexture("enemy_001", "resources/enemies/enemy_001.png");
	loadTexture("enemy_002", "resources/enemies/enemy_002.png");
	loadTexture("enemy_003", "resources/enemies/enemy_003.png");
	
	loadTexture("projectile", "resources/projectile.png");
	loadTexture("projectile_fire", "resources/projectile_fire.png");

	loadTexture("life_1", "resources/life-icons/1.png");
	loadTexture("life_2", "resources/life-icons/2.png");
	loadTexture("life_3", "resources/life-icons/3.png");
	loadTexture("life_4", "resources/life-icons/4.png");
	loadTexture("life_5", "resources/life-icons/5.png");

	loadFont("basis33", "resources/fonts/basis33/basis33.ttf");
}

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::loadFont(const std::string& name, const std::string& font_path)
{
	if (m_font_map.find(name) == m_font_map.end())
	{
		m_font_map[name] = std::make_unique<sf::Font>();
		m_font_map[name]->openFromFile(font_path);
	}
	else
	{
		std::cerr << "Failed to load font `" << name << "` (" << font_path << ")\n"; 
	}
}

void ResourceManager::loadTexture(const std::string& name, const std::string& texture_path)
{
	if (m_texture_map.find(name) == m_texture_map.end())
	{
		m_texture_map[name] = std::make_unique<sf::Texture>();
		m_texture_map[name]->loadFromFile(texture_path);
	}
	else
	{
		std::cerr << "Failed to load texture `" << name << "` (" << texture_path << ")\n"; 
	}
}

const std::unique_ptr<sf::Font>& ResourceManager::getFont(const std::string& name)
{
	return m_font_map[name];
}

const std::unique_ptr<sf::Texture>& ResourceManager::getTexture(const std::string& name)
{
	return m_texture_map[name];
}
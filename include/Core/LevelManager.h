#pragma once

#include <SFML/Graphics.hpp>

#include "DynamicBody.h"
#include "Collider.h"
#include "../Entities/Projectile.h"

class LevelManager
{
private: 
    sf::Vector2u m_size;
    std::vector<std::unique_ptr<Collider>> m_level;
    std::unique_ptr<sf::Sprite> m_tile_sprite;
    std::unique_ptr<sf::RenderTexture> m_blood;
    std::unique_ptr<sf::Sprite> m_blood_sprite;
    std::unique_ptr<sf::Sprite> m_player_icon;

public:
	LevelManager();

	LevelManager(const LevelManager& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;

	static LevelManager& getInstance();

    void load(const std::string& name);
    const std::vector<std::unique_ptr<Collider>>& get();

    void setPlayerIcon(const int hp);
    std::unique_ptr<sf::Sprite>& getPlayerIcon();

    void addBlood(const sf::Vector2f& position, const sf::Color& color);
    void draw(std::unique_ptr<sf::RenderWindow>& target);

    const sf::Vector2u& getSize();
    std::unique_ptr<sf::Sprite>& getTileSprite();
};
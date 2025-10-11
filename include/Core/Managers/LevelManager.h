#pragma once

#include <SFML/Graphics.hpp>

#include "../Collider.h"
#include "../../Utils/Types.h"
#include "../../Entities/DynamicBody.h"
#include "../../Entities/Projectile.h"

class LevelManager
{
private: 
    sf::Vector2u m_size;
    Types::uptr_vec<Collider> m_colliders;
    std::vector<sf::Vector2f> m_spawn_points;

    std::unique_ptr<sf::RenderTexture> m_blood;
    std::unique_ptr<sf::Sprite> m_blood_sprite;
  
    std::unique_ptr<sf::Sprite> m_tile_sprite;
    std::unique_ptr<sf::Sprite> m_player_icon;

    size_t m_current_wave;
    
public:
	LevelManager();

	LevelManager(const LevelManager& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;

	static LevelManager& getInstance();

    void load(const std::string& name);
    const Types::uptr_vec<Collider>& get();
    const std::vector<sf::Vector2f>& getSpawnPoints();

    void setPlayerIcon(const int hp);
    std::unique_ptr<sf::Sprite>& getPlayerIcon();

    void addBlood(const sf::Vector2f& position, const sf::Color& color);
    void draw(std::unique_ptr<sf::RenderWindow>& target);

    const sf::Vector2u& getSize();
    std::unique_ptr<sf::Sprite>& getTileSprite();
};
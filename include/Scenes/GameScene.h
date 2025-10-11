#pragma once

#include "Scene.h"
#include "include/Entities/DynamicBody.h"

#include <functional>
#include <SFML/Audio.hpp>

class GameScene : public Scene
{
private:
    std::unique_ptr<sf::RenderWindow>& m_window;
    float m_calm_time;
    float m_max_calm_time;
    sf::View m_view;

    std::unique_ptr<sf::Text> m_wave_label;

    size_t m_wave;

    DynamicBody* m_player;

    void spawnEnemies();

public:
    GameScene(std::unique_ptr<sf::RenderWindow>& window);
    ~GameScene() override;

    void update(const float& dt) override;
    void pollEvent(const std::optional<sf::Event>& event) override;
    void draw() override;
};

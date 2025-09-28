#pragma once

#include "../Core/Scene.h"
#include "../Core/DynamicBody.h"

class GameScene : public Scene
{
private:
    std::unique_ptr<sf::RenderWindow>& m_window;
    float m_calm_time;
    float m_max_calm_time;

    void spawnEnemies();

public:
    GameScene(std::unique_ptr<sf::RenderWindow>& window);
    ~GameScene() override;

    void update(const float& dt) override;
    void pollEvent(const std::optional<sf::Event>& event) override;
    void draw() override;
};

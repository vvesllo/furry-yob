#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"


class SceneManager
{
private:
	std::unique_ptr<Scene> m_scene;

public:
	SceneManager();

	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

	static SceneManager& getInstance();

	void setScene(std::unique_ptr<Scene>&& scene);

	void update(const float& dt);
	void pollEvent(const std::optional<sf::Event> event);
	void draw();
};
#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <iostream>

class ResourceManager
{
private:
	std::map<std::string, std::unique_ptr<sf::Texture>> m_texture_map;
	std::map<std::string, std::unique_ptr<sf::Font>> m_font_map;

public:
	ResourceManager();

	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator&(const ResourceManager& other) = delete;

	static ResourceManager& getInstance();

	void loadFont(const std::string& name, const std::string& font_path);
	void loadTexture(const std::string& name, const std::string& texture_path);

	const std::unique_ptr<sf::Font>& getFont(const std::string& name);
	const std::unique_ptr<sf::Texture>& getTexture(const std::string& name);
};

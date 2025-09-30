#pragma once

#include <SFML/Graphics.hpp>

class ColorManager
{
private:
    struct Colors {
        sf::Color player;
        sf::Color enemy;
        sf::Color ground;
        sf::Color background;
    } m_colors;

public:
    ColorManager();

    ColorManager(const ColorManager& other) = delete;
    ColorManager& operator=(const ColorManager& other) = delete;
	static ColorManager& getInstance();

    void load();
    const Colors& getColors();
};

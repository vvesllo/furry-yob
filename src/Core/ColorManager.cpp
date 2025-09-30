#include "../../include/Core/ColorManager.h"

#include <fstream>

ColorManager::ColorManager()
{
    m_colors.player = sf::Color::Red;
    m_colors.enemy = sf::Color::Green;
    m_colors.ground = sf::Color::Blue;
    m_colors.background = sf::Color::Black;

    load();
}

ColorManager& ColorManager::getInstance()
{
	static ColorManager instance;
	return instance;
}

void ColorManager::load()
{
    std::ifstream f;
    f.open("resources/colors.txt");

    std::string arg;
    uint32_t color; 

    while (f >> arg >> std::hex >> color)
    {
        if      (arg == "player") m_colors.player = sf::Color(color);
        else if (arg == "enemy") m_colors.enemy = sf::Color(color);
        else if (arg == "background") m_colors.background = sf::Color(color);
        else if (arg == "ground") m_colors.ground = sf::Color(color);
    }
}

const ColorManager::Colors& ColorManager::getColors()
{
    return m_colors;
}


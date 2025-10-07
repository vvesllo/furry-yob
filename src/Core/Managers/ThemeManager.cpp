#include "include/Core/Managers/ThemeManager.h"

#include <fstream>
#include <print>
#include <map>

ThemeManager::ThemeManager()
{
    m_theme.player = sf::Color::Red;
    m_theme.enemy = sf::Color::Green;
    m_theme.ground = sf::Color::Blue;
    m_theme.background = sf::Color::Black;

    load();
}

ThemeManager& ThemeManager::getInstance()
{
	static ThemeManager instance;
	return instance;
}

void ThemeManager::load()
{
    std::ifstream f;
    f.open("resources/theme.txt");

    std::string arg;
    uint32_t value;

    
    std::string name;
    std::map<const std::string, sf::Color> colors;

    while (f >> arg)
    {
        if (arg == "theme") { f >> m_theme.name; continue; }
        else if (arg == "color") 
        {
            f >> name >> std::hex >> value;
            colors[name] = sf::Color(value);
            continue;
        }
        else if (arg == "music")
        {
            f >> name;
            std::println("{}", name);
            m_theme.music.openFromFile(name);
            m_theme.music.setLooping(true);
            continue;
        }
    }

    m_theme.player = colors["player"];
    m_theme.enemy = colors["enemy"];
    m_theme.ground = colors["ground"];
    m_theme.background = colors["background"];

    f.close();
}

const ThemeManager::Theme& ThemeManager::getTheme()
{
    return m_theme;
}

void ThemeManager::playMusic()
{
    m_theme.music.play();
}

void ThemeManager::pauseMusic()
{
    m_theme.music.pause();
}

float easing(float x)
{
    return 1 - (1 - x) * (1 - x);
}

void ThemeManager::finishMusic(const float& dt)
{   
    m_music_t = std::min(5.f, m_music_t + dt) / 5.f;
    m_theme.music.setPitch(std::lerp(m_theme.music.getPitch(), 0.2, easing(m_music_t)));
    m_theme.music.setVolume(std::lerp(m_theme.music.getVolume(), 20, easing(m_music_t)));
}
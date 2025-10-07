#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ThemeManager
{
private:
    struct Theme {
        std::string name;
        sf::Music music;

        sf::Color player;
        sf::Color enemy;
        sf::Color ground;
        sf::Color background;
    } m_theme;

    float m_music_t;

public:
    ThemeManager();

    ThemeManager(const ThemeManager& other) = delete;
    ThemeManager& operator=(const ThemeManager& other) = delete;
	static ThemeManager& getInstance();

    void load();
    
    void playMusic();
    void pauseMusic();
    void finishMusic(const float& dt);

    const Theme& getTheme();
};

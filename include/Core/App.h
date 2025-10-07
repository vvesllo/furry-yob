#pragma once

#include <SFML/Graphics.hpp>

class App
{
private:
    std::unique_ptr<sf::RenderWindow> m_window;
    
    void pollEvent();
    void update(const float& dt);
    void draw();

public:
    App(const unsigned short& width, const unsigned short& height, const char* title);
    ~App();

    void run();
};
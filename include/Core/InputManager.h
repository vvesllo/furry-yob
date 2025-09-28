#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{
private:
    struct Mouse {
        bool right_button;
        bool left_button;

        sf::Vector2f position;
        sf::Vector2f delta;
    } m_mouse;


public:
    InputManager();

    InputManager(const InputManager& other) = delete;
    InputManager& operator=(const InputManager& other) = delete;
	static InputManager& getInstance();

    Mouse& getMouse();
};

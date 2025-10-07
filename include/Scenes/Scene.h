#pragma once

#include <SFML/Graphics.hpp>


class Scene
{
public:
    virtual ~Scene() = default;

    virtual void update(const float& dt) = 0;
    virtual void pollEvent(const std::optional<sf::Event>& event) = 0;
    virtual void draw() = 0;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class DynamicBody
{
private:
    bool m_is_active;

protected:
    std::unique_ptr<sf::Sprite> sprite;
    sf::FloatRect rect;
    
    
    struct {
        sf::Vector2f terminal;
        sf::Vector2f current;
    } velocity;



public:
    DynamicBody(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect);
    virtual ~DynamicBody()=default;


    virtual void update(const float& dt);
    virtual void AI(const float& dt)=0;
    
    void draw(std::unique_ptr<sf::RenderWindow>& target);
    
    const sf::Vector2f getCenter();
    const sf::FloatRect getRect();

    void destroy();
    const bool isActive();
};
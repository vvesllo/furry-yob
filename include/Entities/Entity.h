#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Core/DynamicBody.h"
#include "Projectile.h"

enum class EntityType
{
    Player,
    Enemy,
    Projectile
};

class Entity : public DynamicBody
{
private:
    size_t m_moving_frames_amount;
    
protected:

    enum class LookingDirection {
        Left,
        Right,
    };

    struct {
        sf::Vector2f terminal;
        sf::Vector2f current;
    } velocity;

    struct {
        float speed;
        float acceleration;
        EntityType type;
        LookingDirection looking_direction;
        float health_points;
    } entity_data;
    
    virtual void AI(const float& dt)=0;
    void lookAt(const LookingDirection direction);

public:
    Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect);
    virtual ~Entity()=default;

    void update(const float& dt) override;
    
    const EntityType getType();

    void damage(const float& damage_amount);
    void heal(const float& heal_amount);
};
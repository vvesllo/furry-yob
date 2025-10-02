#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Core/DynamicBody.h"
#include "../Core/Collider.h"
#include "Projectile.h"


enum class EntityType : short
{
    Player,
    Enemy,
    Projectile
};

class Entity : public DynamicBody
{
private:
    size_t m_moving_frames;
    float m_invincibility_time;
    
    enum class ColliderCheckAxis : short
    {
        X, Y
    };
    
    void checkColliding(const ColliderCheckAxis& axis);
    void checkCollidingX(const std::unique_ptr<Collider>& collider);
    void checkCollidingY(const std::unique_ptr<Collider>& collider);

protected:

    enum class LookingDirection : short
    {
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
        float max_health_points;
    } entity_data;

    virtual void AI(const float& dt)=0;
    void dash(const sf::Vector2f& direction);
    void lookAt(const LookingDirection direction);

public:
    Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect);
    virtual ~Entity()=default;

    void update(const float& dt) override;
    
    const EntityType getType();
    const sf::Vector2f getVelocity();

    void damage(const float& damage_amount);
    void heal(const float& heal_amount);

    bool isInvincible();
};
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

class Projectile;

class Entity : public DynamicBody
{
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
        float shot_delay;
        
        float speed;
        float acceleration;
        float dash_delay;
        
        bool standing;
        
        EntityType type;

        float health_points;
        float max_health_points;
    } entity_data;

    virtual void AI(const float& dt)=0;
    void movement(const float& dt);

    void dash(const sf::Vector2f& direction);

    virtual const bool preHit(Entity* sender);
    
    void shootHitscan(const sf::Vector2f& position, const sf::Vector2f& direction, const bool piercing);
    void shootProjectile(
        const std::string& name, 
        const sf::FloatRect& rect, 
        const sf::Vector2f& direction, 
        const float& speed,
        const float& lifetime,
        const bool piercing,
        const std::function<void(Projectile*)> ai);
    
    virtual const std::optional<LookingDirection> processDirection() { return std::nullopt; };
    void lookAt(const std::optional<LookingDirection>& direction);


private:
    size_t m_moving_frames;
    
    bool m_shoot;

    float m_invincibility_time;
    
    float m_shoot_cooldown;
    float m_dash_cooldown;

    LookingDirection m_looking_direction;

    
    enum class ColliderCheckAxis : short { X, Y };
    
    void checkColliding(const ColliderCheckAxis& axis);
    void checkCollidingX(const std::unique_ptr<Collider>& collider);
    void checkCollidingY(const std::unique_ptr<Collider>& collider);
    
public:
    Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect);
    virtual ~Entity()=default;

    void update(const float& dt) override;
    
    const EntityType getType();
    const sf::Vector2f getVelocity();

    void hit(Entity* sender, const float& damage_amount);
    void heal(const float& heal_amount);

    bool isInvincible();
};